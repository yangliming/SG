#include "DirectXHandler.h"
#include "misc.h"

#include <wincodec.h>

using namespace Microsoft::WRL;

DirectXHandler::DirectXHandler() :
	m_windowSizeChangeInProgress(false),
	m_dpi(-1.0f)
{
}

DirectXHandler::~DirectXHandler()
{
}

void DirectXHandler::Initialize()
{
	CreateDeviceIndependentResources();
	CreateDeviceResources();
}

void DirectXHandler::CreateDeviceIndependentResources()
{
	D2D1_FACTORY_OPTIONS options;
	ZeroMemory(&options, sizeof(D2D1_FACTORY_OPTIONS));

#if defined(_DEBUG)
	options.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
#endif

	DX::ThrowIfFailed(
		D2D1CreateFactory(
			D2D1_FACTORY_TYPE_SINGLE_THREADED,
			__uuidof(ID2D1Factory2),
			&options,
			&m_d2dFactory)
	);

	DX::ThrowIfFailed(
		DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(IDWriteFactory2),
			&m_dwriteFactory)
	);

	DX::ThrowIfFailed(
		CoCreateInstance(
			CLSID_WICImagingFactory,
			nullptr,
			CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS(&m_wicFactory))
	);
}

void DirectXHandler::CreateDeviceResources()
{
	UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
	ComPtr<IDXGIDevice> dxgiDevice;

#if defined(_DEBUG)
	if (DX::SdkLayersAvailable())
	{
		creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
	}
#endif

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

	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> context;
	ComPtr<IDXGISwapChain> swapChain;

	DX::ThrowIfFailed(
		D3D11CreateDevice(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			0,
			creationFlags,
			featureLevels,
			ARRAYSIZE(featureLevels),
			D3D11_SDK_VERSION,
			&device,
			&m_featureLevel,
			&context)
	);

	DX::ThrowIfFailed(
		device.As(&m_d3dDevice)
	);

	DX::ThrowIfFailed(
		context.As(&m_d3dContext)
	);

	DX::ThrowIfFailed(
		m_d3dDevice.As(&dxgiDevice)
	);

	DX::ThrowIfFailed(
		m_d2dFactory->CreateDevice(dxgiDevice.Get(), &m_d2dDevice)
	);

	DX::ThrowIfFailed(
		m_d2dDevice->CreateDeviceContext(
			D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
			&m_d2dContext)
	);
}

void DirectXHandler::CreateWindowSizeDependentResources()
{
	if (m_swapChain != nullptr)
	{
		HRESULT hr = m_swapChain->ResizeBuffers(2, 0, 0, DXGI_FORMAT_B8G8R8A8_UNORM, 0);

		if (hr == DXGI_ERROR_DEVICE_REMOVED)
		{
			//HandleDeviceLost();
			return;
		}
		else
		{
			DX::ThrowIfFailed(hr);
		}
	}
	else
	{
		DXGI_SWAP_CHAIN_DESC1 swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC1));


	}
}