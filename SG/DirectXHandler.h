// Credit towards TextInterop.sln from Microsoft Example
// https://code.msdn.microsoft.com/windowsapps/Direct2D-Direct3D-Interop-ee641e46/view/SourceCode

#ifndef DIRECTXHANDLER_H
#define DIRECTXHANDLER_H

#include <wrl.h>
#include <d2d1_2.h>
#include <d2d1effects_1.h>
#include <d3d11_2.h>
#include <dwrite_2.h>

class DirectXHandler
{
public:
	DirectXHandler();
	~DirectXHandler();

	void Initialize();
	void UpdateWindowSize();

	void SetDpi(float dpi);

	void HandleDeviceLost();
	void ValidateDevice();
private:

	// DirectWrite and Windows Imaging Component Objects
	Microsoft::WRL::ComPtr<IDWriteFactory2> m_dwriteFactory;
	Microsoft::WRL::ComPtr<IWICImagingFactory> m_wicFactory;

	// DirectX Core Objects
	Microsoft::WRL::ComPtr<ID3D11Device2> m_d3dDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext2> m_d3dContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain1> m_swapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_d3dRenderTargetView;
	
	// Direct2D Objects
	Microsoft::WRL::ComPtr<ID2D1Factory2> m_d2dFactory;
	Microsoft::WRL::ComPtr<ID2D1Device1> m_d2dDevice;
	Microsoft::WRL::ComPtr<ID2D1DeviceContext1> m_d2dContext;
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> m_d2dTargetBitmap;

	// Direct3D Objects
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_d3dDepthStencilView;

	// Render Properties
	D3D_FEATURE_LEVEL m_featureLevel;
	float m_dpi;
	bool m_windowSizeChangeInProgress;

	void CreateDeviceIndependentResources();
	void CreateDeviceResources();
	void CreateWindowSizeDependentResources();
};

#endif // DIRECTXHANDLER_H