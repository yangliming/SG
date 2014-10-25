#include "GraphicHandler.h"
#include <map>
#include "DirectXHandler.h"
#include "TextureHandler.h"
#include "Camera.h"
#include "GameState.h"

#include <DirectXMath.h>

using namespace DirectX;

namespace GraphicHandler
{
	// Private Members
	namespace
	{
		DirectXHandler* XHandler = nullptr;
		TextureHandler* THandler = nullptr;
		Camera* CHandler = nullptr;

		std::list<DrawObject*> DrawHandler;

		// Constants
		const int WINDOW_WIDTH = 800;
		const int WINDOW_HEIGHT = 600;
		LPCSTR WND_CLASS_NAME = "SGMainWindow";
		LPCSTR WINDOW_NAME = "SG";

		// Windows Objects
		HWND HWnd;
		WNDCLASSEX WindowClass;
		HINSTANCE HInstance;

		LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			GameState::HandleInput(message, wParam, lParam);

			if (message == WM_DESTROY)
			{
				PostQuitMessage(0);
				return 0;
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
	}

	void Initialize(HINSTANCE hInstance)
	{
		CoInitialize(nullptr);

		HInstance = hInstance;
		CreateWindowClass();

		XHandler = new DirectXHandler(HWnd, WINDOW_WIDTH, WINDOW_HEIGHT);
		XHandler->initialize();
		XHandler->initScene();

		THandler = new TextureHandler(XHandler->getD3DDevice(), XHandler->getD3DDeviceContext());

		CHandler = new Camera();
		CHandler->setPosition(0, 0, 0);
		CHandler->setViewParameters(
			XMFLOAT3(0.0f, 0.0f, -0.5f),
			XMFLOAT3(0.0f, 0.0f, 0.0f),
			XMFLOAT3(0.0f, 1.0f, 0.0f));
		CHandler->setOrthoProj(
			800,
			600,
			-1,
			1);
	}

	void CleanUp()
	{
		CoUninitialize();

		delete CHandler;
		delete THandler;
		delete XHandler;
	}

	void ShowWindow(int nCmdShow)
	{
		ShowWindow(HWnd, nCmdShow);
	}

	WPARAM Update(void (*Render)(void))
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

			if (Render)
			{
				(*Render)();
			}

			XHandler->render(CHandler, THandler, DrawHandler);
			XHandler->present();
		}

		return msg.wParam;
	}

	TIID LoadTexture(std::wstring filename)
	{
		return THandler->loadTexture(filename);
	}

	void RegisterDrawObject(DrawObject* obj)
	{
		DrawHandler.push_back(obj);
	}

	void UnRegisterDrawObject(DrawObject* obj)
	{
		DrawHandler.remove(obj);
	}
}