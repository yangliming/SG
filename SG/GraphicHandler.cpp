#include "GraphicHandler.h"
#include <map>
#include "DirectXHandler.h"
#include "TextureHandler.h"
#include "Camera.h"

#include <DirectXMath.h>

using namespace DirectX;

namespace GraphicHandler
{
	// Private Members
	namespace
	{
		DirectXHandler* XHandler;
		TextureHandler* THandler;
		Camera* CHandler;
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

		// GraphicHandler Types
		struct GraphicHandlerTexture
		{
			TIID tID;
			float X;
			float Y;
			float ZLevel;
			float Width;
			float Height;
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
		THandler->loadTexture(L"background.bmp");

		CHandler = new Camera();
		CHandler->setPosition(0, 0, 0);
		CHandler->setViewParameters(
			XMFLOAT3(0.0f, 0.0f, -0.5f),
			XMFLOAT3(0.0f, 0.0f, 0.0f),
			XMFLOAT3(0.0f, 1.0f, 0.0f));
		CHandler->setOrthoProj(
			10,
			10,
			-1,
			1);

		GraphicObjects.clear();
	}

	void CleanUp()
	{
		CoUninitialize();

		delete XHandler;
		delete THandler;
		delete CHandler;
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