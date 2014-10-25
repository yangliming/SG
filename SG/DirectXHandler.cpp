#include "DirectXHandler.h"
#include "misc.h"
#include "Global.h"
#include "TextureHandler.h"
#include "Camera.h"

#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d2d1.lib")
#pragma comment (lib, "dwrite.lib")
#pragma comment (lib, "d3dcompiler.lib")

struct VERTEX
{
	unsigned int index;
	VECTOR3 Position;
	TEXCOORD TexCoords;

	VERTEX(unsigned int ind, float x, float y, float z, float u, float v)
	{
		index = ind;
		Position.X = x;
		Position.Y = y;
		Position.Z = z;
		TexCoords.U = u;
		TexCoords.V = v;
	}
};

using namespace DirectX;

DirectXHandler::DirectXHandler(HWND hwnd, int width, int height) :
	m_hwnd(hwnd),
	m_windowWidth(width),
	m_windowHeight(height)
{
}

DirectXHandler::~DirectXHandler()
{
	// Release DXGI Objects
	SafeRelease(&m_swapChain);

	// Release Direct3D Objects
	SafeRelease(&m_d3dDevice);
	SafeRelease(&m_d3dContext);
	SafeRelease(&m_d3dRenderTargetView);
	SafeRelease(&m_d3dVertexShader);
	SafeRelease(&m_d3dPixelShader);

	SafeRelease(&m_d3dVertexShader);
	SafeRelease(&m_d3dPixelShader);
	SafeRelease(&m_d3dInputLayout);
	SafeRelease(&m_d3dSamplerState);
	SafeRelease(&m_d3dVertexBuffer);
	SafeRelease(&m_d3dCBCamera);
	SafeRelease(&m_d3dCBVertex);

	// Release Direct2D Objects
	SafeRelease(&m_d2dFactory);
	SafeRelease(&m_d2dDevice);
	SafeRelease(&m_d2dContext);
	SafeRelease(&m_d2dTargetBitmap);

	// Release DirectWriteObjects
	SafeRelease(&m_dwriteFactory);
	SafeRelease(&m_textFormat);
}

void DirectXHandler::initialize()
{
	initD3D();
	initD2D();
	initDirectWrite();
	initSwapChain();
	initView();
	initInterop();
}

void DirectXHandler::initScene()
{
	loadShaders();
	loadData();
}

void DirectXHandler::render(Camera* cam, TextureHandler* textures, std::list<DrawObject*> toDraw)
{
	float color[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	m_d3dContext->ClearRenderTargetView(m_d3dRenderTargetView, color);

	XMMATRIX m_wvp = cam->getMatrix();
	m_d3dContext->UpdateSubresource(m_d3dCBCamera, 0, nullptr, &m_wvp, 0, 0);
	m_d3dContext->VSSetConstantBuffers(0, 1, &m_d3dCBCamera);

	auto iter = toDraw.begin();
	while (iter != toDraw.end())
	{
		PDRAWVALS vals = (*iter)->GetDrawValues();
		if (vals->draw)
		{	
			ID3D11ShaderResourceView* view = textures->getShaderResourceView(vals->tIID);
			m_d3dContext->PSSetShaderResources(0, 1, &view);

			prepareDraw(vals);
			m_d3dContext->Draw(4, 0);
		}
		iter++;
	}	
}

void DirectXHandler::present()
{
	m_swapChain->Present(0, 0);
}

ID3D11Device* DirectXHandler::getD3DDevice()
{
	return m_d3dDevice;
}

ID3D11DeviceContext* DirectXHandler::getD3DDeviceContext()
{
	return m_d3dContext;
}

void DirectXHandler::initD3D()
{
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};

	UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#if _DEBUG
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	DX::ThrowIfFailed(
		D3D11CreateDevice(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			0,
			creationFlags,
			featureLevels,
			ARRAYSIZE(featureLevels),
			D3D11_SDK_VERSION,
			&m_d3dDevice,
			&m_featureLevel,
			&m_d3dContext)
	);
}

void DirectXHandler::initD2D()
{
	D2D1_FACTORY_OPTIONS options;
	ZeroMemory(&options, sizeof(D2D1_FACTORY_OPTIONS));

	DX::ThrowIfFailed(
		D2D1CreateFactory(
			D2D1_FACTORY_TYPE_SINGLE_THREADED,
			__uuidof(ID2D1Factory2),
			&options,
			(void**)&m_d2dFactory)
	);

	IDXGIDevice* dxgiDevice;
	DX::ThrowIfFailed(
		m_d3dDevice->QueryInterface(&dxgiDevice)
	);

	DX::ThrowIfFailed(
		m_d2dFactory->CreateDevice(dxgiDevice, &m_d2dDevice)
	);

	DX::ThrowIfFailed(
		m_d2dDevice->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &m_d2dContext)
	);

	SafeRelease(&dxgiDevice);
}

void DirectXHandler::initDirectWrite()
{
	DX::ThrowIfFailed(
		DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(IDWriteFactory),
			(IUnknown**)&m_dwriteFactory)
	);

	DX::ThrowIfFailed(
		m_dwriteFactory->CreateTextFormat(
			L"Arial",
			nullptr,
			DWRITE_FONT_WEIGHT_REGULAR,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			72.0f,
			L"en-us",
			(IDWriteTextFormat**)&m_textFormat)
	);

	DX::ThrowIfFailed(
		m_textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER)
	);

	DX::ThrowIfFailed(
		m_textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER)
	);
}

void DirectXHandler::initSwapChain()
{
	// Create SwapChain
	DXGI_MODE_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));

	bufferDesc.Width = m_windowWidth;
	bufferDesc.Height = m_windowHeight;
	bufferDesc.RefreshRate.Numerator = 60;
	bufferDesc.RefreshRate.Denominator = 1;
	bufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc = bufferDesc;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = m_hwnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Windowed = true;

	IDXGIDevice* dxgiDevice;
	DX::ThrowIfFailed(
		m_d3dDevice->QueryInterface(&dxgiDevice)
	);

	IDXGIAdapter* dxgiAdaptor;
	DX::ThrowIfFailed(
		dxgiDevice->GetAdapter(&dxgiAdaptor)
	);

	IDXGIFactory2* dxgiFactory;
	DX::ThrowIfFailed(
		dxgiAdaptor->GetParent(IID_PPV_ARGS(&dxgiFactory))
	);

	DX::ThrowIfFailed(
		dxgiFactory->CreateSwapChain(m_d3dDevice, &swapChainDesc, &m_swapChain)
	);

	SafeRelease(&dxgiDevice);
	SafeRelease(&dxgiAdaptor);
	SafeRelease(&dxgiFactory);
}

void DirectXHandler::initView()
{
	// Create Render Target
	ID3D11Texture2D* backBuffer;
	m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
	m_d3dDevice->CreateRenderTargetView(backBuffer, nullptr, &m_d3dRenderTargetView);
	backBuffer->Release();

		// add depth stencil view here
	m_d3dContext->OMSetRenderTargets(1, &m_d3dRenderTargetView, nullptr);

	CD3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(CD3D11_VIEWPORT));
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = m_windowWidth;
	viewport.Height = m_windowHeight;

	m_d3dContext->RSSetViewports(1, &viewport);
}

void DirectXHandler::initInterop()
{
	D2D1_BITMAP_PROPERTIES1 bitmapProperties =
		D2D1::BitmapProperties1(
			D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
			D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
			96.0f,
			96.0f);

	IDXGISurface* dxgiBackBuffer;
	DX::ThrowIfFailed(
		m_swapChain->GetBuffer(0, IID_PPV_ARGS(&dxgiBackBuffer))
	);

	DX::ThrowIfFailed(
		m_d2dContext->CreateBitmapFromDxgiSurface(
			dxgiBackBuffer,
			&bitmapProperties,
			&m_d2dTargetBitmap)
	);
	SafeRelease(&dxgiBackBuffer);

	m_d2dContext->SetTarget(m_d2dTargetBitmap);
	m_d2dContext->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);
}

void DirectXHandler::loadShaders()
{
	ID3DBlob* VertexShaderBlob;
	ID3DBlob* PixelShaderBlob;

	UINT creationFlags = 0;
#if _DEBUG
	creationFlags = D3DCOMPILE_DEBUG;
#endif

	DX::ThrowIfFailed(
		D3DCompileFromFile(
			L"VertexShader.hlsl", 
			0,
			0, 
			"main", 
			"vs_4_0", 
			creationFlags, 
			0, 
			&VertexShaderBlob, 
			nullptr)
	);

	DX::ThrowIfFailed(
		D3DCompileFromFile(
			L"PixelShader.hlsl",
			0, 
			0, 
			"main", 
			"ps_4_0", 
			creationFlags,
			0, 
			&PixelShaderBlob, 
			nullptr)
	);

	DX::ThrowIfFailed(
		m_d3dDevice->CreateVertexShader(
			VertexShaderBlob->GetBufferPointer(),
			VertexShaderBlob->GetBufferSize(),
			nullptr,
			&m_d3dVertexShader)
	);

	DX::ThrowIfFailed(
		m_d3dDevice->CreatePixelShader(
			PixelShaderBlob->GetBufferPointer(), 
			PixelShaderBlob->GetBufferSize(),
			nullptr, 
			&m_d3dPixelShader)
	);

	m_d3dContext->VSSetShader(m_d3dVertexShader, 0, 0);
	m_d3dContext->PSSetShader(m_d3dPixelShader, 0, 0);

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "INDEX", 0, DXGI_FORMAT_R32_UINT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 4, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	DX::ThrowIfFailed(
		m_d3dDevice->CreateInputLayout(
		layout,
		ARRAYSIZE(layout),
		VertexShaderBlob->GetBufferPointer(),
		VertexShaderBlob->GetBufferSize(),
		&m_d3dInputLayout)
		);

	m_d3dContext->IASetInputLayout(m_d3dInputLayout);
	m_d3dContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
}

void DirectXHandler::loadData()
{
	// Load Vertex Data
	VERTEX v[] =
	{
		VERTEX(0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f),
		VERTEX(1, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f),
		VERTEX(2, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f),
		VERTEX(3, 1.0f, -1.0f, 0.0f, 1.0f, 1.0f)
	};

	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(D3D11_BUFFER_DESC));

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VERTEX)* 4;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData;
	ZeroMemory(&vertexBufferData, sizeof(D3D11_SUBRESOURCE_DATA));
	vertexBufferData.pSysMem = v;

	DX::ThrowIfFailed(
		m_d3dDevice->CreateBuffer(
			&vertexBufferDesc, 
			&vertexBufferData, 
			&m_d3dVertexBuffer)
	);

	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	m_d3dContext->IASetVertexBuffers(0, 1, &m_d3dVertexBuffer, &stride, &offset);

	// Load Sampler
	D3D11_SAMPLER_DESC sampleDesc;
	ZeroMemory(&sampleDesc, sizeof(D3D11_SAMPLER_DESC));
	sampleDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampleDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampleDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampleDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

	DX::ThrowIfFailed(
		m_d3dDevice->CreateSamplerState(&sampleDesc, &m_d3dSamplerState)
	);

	m_d3dContext->PSSetSamplers(0, 1, &m_d3dSamplerState);

	// Create Constant Buffer
	D3D11_BUFFER_DESC cbDesc;
	ZeroMemory(&cbDesc, sizeof(D3D11_BUFFER_DESC));
	cbDesc.Usage = D3D11_USAGE_DEFAULT;
	cbDesc.ByteWidth = sizeof(XMMATRIX);
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = 0;
	cbDesc.MiscFlags = 0;

	DX::ThrowIfFailed(
		m_d3dDevice->CreateBuffer(&cbDesc, nullptr, &m_d3dCBCamera)
	);

	cbDesc.ByteWidth = sizeof(XMMATRIX) * 4;

	DX::ThrowIfFailed(
		m_d3dDevice->CreateBuffer(&cbDesc, nullptr, &m_d3dCBVertex)
	);
}

void DirectXHandler::prepareDraw(PDRAWVALS vals)
{
	XMMATRIX vX[4];

	XMMATRIX objTrans = XMMatrixTranslation(vals->x, vals->y, vals->z);
	XMMATRIX widthTrans = XMMatrixTranslation(vals->width, 0, 0);
	XMMATRIX heightTrans = XMMatrixTranslation(0, vals->height, 0);

	vX[0] = objTrans * heightTrans;
	vX[1] = objTrans * widthTrans * heightTrans;
	vX[2] = objTrans;
	vX[3] = objTrans * widthTrans;

	vX[0] = XMMatrixTranspose(vX[0]);
	vX[1] = XMMatrixTranspose(vX[1]);
	vX[2] = XMMatrixTranspose(vX[2]);
	vX[3] = XMMatrixTranspose(vX[3]);

	m_d3dContext->UpdateSubresource(m_d3dCBVertex, 0, nullptr, vX, 0, 0);
	m_d3dContext->VSSetConstantBuffers(1, 1, &m_d3dCBVertex);
}