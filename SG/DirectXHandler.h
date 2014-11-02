// Credit towards TextInterop.sln from Microsoft Example
// https://code.msdn.microsoft.com/windowsapps/Direct2D-Direct3D-Interop-ee641e46/view/SourceCode

#ifndef DIRECTXHANDLER_H
#define DIRECTXHANDLER_H

#include <wrl.h>
#include <d2d1_2.h>
#include <d2d1effects_1.h>
#include <d3d11_2.h>
#include <dwrite_2.h>

#include <list>
#include "DrawObject.h"

class TextureHandler;
class Camera;

class DirectXHandler
{
public:
	DirectXHandler(HWND hwnd, int width, int height);
	virtual ~DirectXHandler();

	void initialize();
	void initScene();

	void render(Camera* cam, TextureHandler* textures, std::list<DrawObject*> toDraw);
	void present();

	ID3D11Device* getD3DDevice();
	ID3D11DeviceContext* getD3DDeviceContext();
private:

	// Window Properties
	HWND m_hwnd;
	int m_windowHeight;
	int m_windowWidth;

	// DXGI Objects
	IDXGISwapChain* m_swapChain;

	// Direct3D Objects
	ID3D11Device* m_d3dDevice;
	ID3D11DeviceContext* m_d3dContext;
	ID3D11RenderTargetView* m_d3dRenderTargetView;

	ID3D11VertexShader* m_d3dVertexShader;
	ID3D11PixelShader* m_d3dPixelShader;
	
	ID3D11InputLayout* m_d3dInputLayout;
	ID3D11SamplerState* m_d3dSamplerState;

	ID3D11DepthStencilView* m_d3dDepthStencilView;
	ID3D11Texture2D* m_d3dDepthStencilBuffer;
	ID3D11BlendState* m_d3dBlendState;

	ID3D11Buffer* m_d3dVertexBuffer;
	ID3D11Buffer* m_d3dCBCamera;
	ID3D11Buffer* m_d3dCBVertex;

	// Direct2D Objects
	ID2D1Factory2* m_d2dFactory;
	ID2D1Device1* m_d2dDevice;
	ID2D1DeviceContext1* m_d2dContext;
	ID2D1Bitmap1* m_d2dTargetBitmap;

	// DirectWrite Objects
	IDWriteFactory2* m_dwriteFactory;
	IDWriteTextFormat1* m_textFormat;

	// Render Properties
	D3D_FEATURE_LEVEL m_featureLevel;

	// Init Functions
	void initD3D();
	void initD2D();
	void initDirectWrite();
	void initSwapChain();
	void initView();
	void initInterop();
	void initCamera();

	// Scene Functions
	void loadShaders();
	void loadData();
	void prepareDraw(PDRAWVALS vals);
};

#endif // DIRECTXHANDLER_H