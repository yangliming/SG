#include "GraphicHandler.h"
#include <map>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")

#include <d3d11.h>
#include <d3dcompiler.h>
#include <dxgi.h>

#include "DirectXTK\Inc\WICTextureLoader.h"
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include <DirectXCollision.h>

using namespace DirectX;

namespace GraphicHandler
{
	// Private Members
	namespace
	{
		// Constants
		const int WINDOW_WIDTH = 800;
		const int WINDOW_HEIGHT = 600;
		LPCSTR WND_CLASS_NAME = "SGMainWindow";
		LPCSTR WINDOW_NAME = "SG";

		// Windows Objects
		HWND HWnd;
		WNDCLASSEX WindowClass;
		HINSTANCE HInstance;

		// DirectX Objects
		IDXGISwapChain *D3DSwapChain;
		ID3D11Device *D3DDevice;
		ID3D11DeviceContext *D3DContext;
		ID3D11RenderTargetView* D3DBackBuffer;
		ID3D11InputLayout* D3DInputLayout;
		ID3D11VertexShader* D3DVertexShader;
		ID3D11PixelShader* D3DPixelShader;
		ID3D11Buffer* D3DVertexBuffer;

		// Texture Objects
		ID3D11Resource* D3DBackgroundTexture;
		ID3D11SamplerState* D3DSamplerState;

		// Constant Objects
		ID3D11Buffer* D3DConstantBuffer;
		XMMATRIX MWVP;
		XMMATRIX MWorld;
		XMMATRIX MCameraView;
		XMMATRIX MCameraProjection;
		XMVECTOR MCameraPosition;
		XMVECTOR MCameraTarget;
		XMVECTOR MCameraUp;

		// GraphicHandler Types
		struct GraphicHandlerTexture
		{
			ID3D11ShaderResourceView* ShaderResourceView;
			int X;
			int Y;
			int ZLevel;
			int Width;
			int Height;
			bool Draw;
		};

		// GraphicHandler Objects
		std::map<int, GraphicHandlerTexture> GraphicObjects;
		int NextID;

		LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			switch(message)
			{
				case WM_DESTROY:
					{
						PostQuitMessage(0);
						return 0;
					} break;
			}

			return DefWindowProc (hWnd, message, wParam, lParam);
		}

		void CreateWindowClass()
		{
			ZeroMemory(&WindowClass, sizeof(WNDCLASSEX));

			WindowClass.cbSize = sizeof(WNDCLASSEX);
			WindowClass.style = CS_HREDRAW | CS_VREDRAW;
			WindowClass.lpfnWndProc = WindowProc;
			WindowClass.hInstance = HInstance;
			WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
			WindowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
			WindowClass.lpszClassName = WND_CLASS_NAME;

			RegisterClassEx(&WindowClass);
			HWnd = CreateWindowEx(NULL,
								  WND_CLASS_NAME,
								  WINDOW_NAME,
								  WS_OVERLAPPEDWINDOW,
								  CW_USEDEFAULT,
								  CW_USEDEFAULT,
								  WINDOW_WIDTH,
								  WINDOW_HEIGHT,
								  NULL,
								  NULL,
								  HInstance,
								  NULL);
		}

		void InitD3D()
		{
			DXGI_MODE_DESC bufferDesc;
			ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));

			bufferDesc.Width = WINDOW_WIDTH;
			bufferDesc.Height = WINDOW_HEIGHT;
			bufferDesc.RefreshRate.Numerator = 60;
			bufferDesc.RefreshRate.Denominator = 1;
			bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
			bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

			DXGI_SWAP_CHAIN_DESC swapChainDesc;
			ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

			swapChainDesc.BufferCount = 1;
			swapChainDesc.BufferDesc = bufferDesc;
			swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			swapChainDesc.OutputWindow = HWnd;
			swapChainDesc.SampleDesc.Count = 1;
			swapChainDesc.SampleDesc.Quality = 0;
			swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
			swapChainDesc.Windowed = TRUE;

			D3D11CreateDeviceAndSwapChain(NULL,
										  D3D_DRIVER_TYPE_HARDWARE,
										  NULL,
										  NULL,
										  NULL,
										  NULL,
										  D3D11_SDK_VERSION,
										  &swapChainDesc,
										  &D3DSwapChain,
										  &D3DDevice,
										  NULL,
										  &D3DContext);

			ID3D11Texture2D* backBuffer;

			D3DSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
			D3DDevice->CreateRenderTargetView(backBuffer, NULL, &D3DBackBuffer);
			backBuffer->Release();

			D3DContext->OMSetRenderTargets(1, &D3DBackBuffer, NULL);
		}
	}

	void Initialize(HINSTANCE hInstance)
	{
		HInstance = hInstance;
		CreateWindowClass();
		InitD3D();

		GraphicObjects.clear();
		NextID = 0;
	}

	// most likely will need many variants of this depending on the level, etc.
	// for the meantime, stay with this
	void InitScene()
	{
		// Load Shaders
		ID3DBlob* VertexShaderBlob;
		ID3DBlob* PixelShaderBlob;

		HRESULT hr;

		// For some reason target version vs_5_0 does not work
		hr = D3DCompileFromFile(L"VertexShader.hlsl", 0, 0, "main", "vs_4_0", D3DCOMPILE_DEBUG, 0, &VertexShaderBlob, NULL);
		hr = D3DCompileFromFile(L"PixelShader.hlsl", 0, 0, "main", "ps_4_0", D3DCOMPILE_DEBUG, 0, &PixelShaderBlob, NULL);

		hr = D3DDevice->CreateVertexShader(VertexShaderBlob->GetBufferPointer(), VertexShaderBlob->GetBufferSize(), NULL, &D3DVertexShader);
		hr = D3DDevice->CreatePixelShader(PixelShaderBlob->GetBufferPointer(), PixelShaderBlob->GetBufferSize(), NULL, &D3DPixelShader);

		D3DContext->VSSetShader(D3DVertexShader, 0, 0);
		D3DContext->PSSetShader(D3DPixelShader, 0, 0);

		// Temporary Vertex Loads
		

		VERTEX v[] =
		{
			VERTEX(-1.0f, 1.0f, 0.0f, 0.0f, 0.0f),
			VERTEX(1.0f, 1.0f, 0.0f, 1.0f, 0.0f),
			VERTEX(-1.0f, -1.0f, 0.0f, 0.0f, 1.0f),
			VERTEX(1.0f, -1.0f, 0.0f, 1.0f, 1.0f)
		};

		D3D11_BUFFER_DESC vertexBufferDesc;
		ZeroMemory(&vertexBufferDesc, sizeof(D3D11_BUFFER_DESC));

		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDesc.ByteWidth = sizeof(VERTEX) * 4;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = 0;
		vertexBufferDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA vertexBufferData;
		ZeroMemory(&vertexBufferData, sizeof(D3D11_SUBRESOURCE_DATA));
		vertexBufferData.pSysMem = v;
		
		hr = D3DDevice->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &D3DVertexBuffer);

		UINT stride = sizeof(VERTEX);
		UINT offset = 0;
		D3DContext->IASetVertexBuffers(0, 1, &D3DVertexBuffer, &stride, &offset);

		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
		};

		hr = D3DDevice->CreateInputLayout(layout, ARRAYSIZE(layout), VertexShaderBlob->GetBufferPointer(), VertexShaderBlob->GetBufferSize(), &D3DInputLayout);
		D3DContext->IASetInputLayout(D3DInputLayout);
		D3DContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		// Set the Viewport
		D3D11_VIEWPORT viewport;
		ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = WINDOW_WIDTH;
		viewport.Height = WINDOW_HEIGHT;

		D3DContext->RSSetViewports(1, &viewport);

		D3D11_SAMPLER_DESC sampleDesc;
		ZeroMemory(&sampleDesc, sizeof(D3D11_SAMPLER_DESC));
		sampleDesc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
		sampleDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampleDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampleDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		
		hr = D3DDevice->CreateSamplerState(&sampleDesc, &D3DSamplerState);
		D3DContext->PSSetSamplers(0, 1, &D3DSamplerState);

		// Create Constant Buffer
		D3D11_BUFFER_DESC cbDesc;
		ZeroMemory(&cbDesc, sizeof(D3D11_BUFFER_DESC));
		cbDesc.Usage = D3D11_USAGE_DEFAULT;
		cbDesc.ByteWidth = sizeof(DirectX::XMMATRIX);
		cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbDesc.CPUAccessFlags = 0;
		cbDesc.MiscFlags = 0;

		hr = D3DDevice->CreateBuffer(&cbDesc, NULL, &D3DConstantBuffer);

		MCameraPosition = XMVectorSet(0.0f, 0.0f, -0.5f, 0.0f);
		MCameraTarget = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		MCameraUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	}

	void ShowWindow(int nCmdShow)
	{
		ShowWindow(HWnd, nCmdShow);
	}

	WPARAM Update(void (*Render)(void), int fps)
	{
		MSG msg;
		while(TRUE)
		{
			if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);

				if(msg.message == WM_QUIT)
					break;
			}

			float color[] = {0.0f, 0.0f, 0.0f, 1.0f};

			D3DContext->ClearRenderTargetView(D3DBackBuffer, color);

			XMMATRIX t1 = MCameraView = XMMatrixLookAtLH(MCameraPosition, MCameraTarget, MCameraUp);
			XMMATRIX t2 = MCameraProjection = XMMatrixOrthographicLH(10, 10, 0, 1);
			XMMATRIX t3 = MWorld = XMMatrixIdentity();
			

			D3DContext->UpdateSubresource(D3DConstantBuffer, 0, NULL, &MWVP, 0, 0);
			D3DContext->VSSetConstantBuffers(0, 1, &D3DConstantBuffer);

			auto iter = GraphicObjects.begin();
			while (iter != GraphicObjects.end())
			{
				GraphicHandlerTexture toDraw = (*iter).second;
				if (toDraw.Draw)
				{
					MWorld = XMMatrixTranslation(toDraw.X, toDraw.Y, toDraw.ZLevel / 10);
					MWVP = MWorld * MCameraView * MCameraProjection;
					MWVP = XMMatrixTranspose(MWVP);

					D3DContext->PSSetShaderResources(0, 1, &(*iter).second.ShaderResourceView);
					D3DContext->UpdateSubresource(D3DConstantBuffer, 0, NULL, &MWVP, 0, 0);
					D3DContext->VSSetConstantBuffers(0, 1, &D3DConstantBuffer);

					D3DContext->Draw(4, 0);
				}
				iter++;
			}

			if (Render != nullptr)
				(*Render)();

			D3DSwapChain->Present(0, 0);
		}

		return msg.wParam;
	}

	void CleanUp()
	{
		if (D3DSwapChain != NULL)
			D3DSwapChain->Release();
		if (D3DDevice != NULL)
			D3DDevice->Release();
		if (D3DContext != NULL)
			D3DContext->Release();
		if (D3DBackBuffer != NULL)
			D3DBackBuffer->Release();
		if (D3DInputLayout != NULL)
			D3DInputLayout->Release();
		if (D3DVertexShader != NULL)
			D3DVertexShader->Release();
		if (D3DPixelShader != NULL)
			D3DPixelShader->Release();
		if (D3DVertexBuffer != NULL)
			D3DVertexBuffer->Release();

		if (D3DBackgroundTexture != NULL)
			D3DBackgroundTexture->Release();
		if (D3DSamplerState != NULL)
			D3DSamplerState->Release();

		if (D3DConstantBuffer != NULL)
			D3DConstantBuffer->Release();
	}

	void LoadTexture(std::wstring filename, ID3D11Resource** texture, ID3D11ShaderResourceView** resource)
	{
		CreateWICTextureFromFile(D3DDevice, D3DContext, filename.data(), texture, resource);
	}

	int AddTexture(ID3D11ShaderResourceView* resource, int x, int y, int zlevel, int width, int height, bool draw)
	{
		GraphicHandlerTexture tex;
		tex.ShaderResourceView = resource;
		tex.X = x;
		tex.Y = y;
		tex.ZLevel = zlevel;
		tex.Width = width;
		tex.Height = height;
		
		GraphicObjects[NextID] = tex;
		NextID++;

		return NextID - 1;
	}

	void RemoveTexture(int id)
	{
		GraphicObjects.erase(id);
	}

	void ChangeTextureX(int id, int x)
	{
		GraphicObjects[id].X = x;
	}

	void ChangeTextureY(int id, int y)
	{
		GraphicObjects[id].Y = y;
	}

	void ChangeTextureZLevel(int id, int zlevel)
	{
		GraphicObjects[id].ZLevel = zlevel;
	}

	void ChangeTextureWidth(int id, int width)
	{
		GraphicObjects[id].Width = width;
	}

	void ChangeTextureHeight(int id, int height)
	{
		GraphicObjects[id].Height = height;
	}

	void ChangeTextureDraw(int id, bool draw)
	{
		GraphicObjects[id].Draw = draw;
	}
}