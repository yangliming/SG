#include <windows.h>
#include <windowsx.h>

#include "Global.h"
#include "GraphicHandler.h"
#include "Texture.h"

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
	GraphicHandler::Initialize(hInstance);
	GraphicHandler::ShowWindow(nCmdShow);
	GraphicHandler::InitScene();

	Texture tex(L"background.bmp", 0, 0, 0, 1, 1, true);
	Texture tex2(L"background.bmp", 1, 1, 1, 3, 3, true);
	Texture tex3(L"background.bmp", -3, -3, 1, 3, 3, true);

	WPARAM retvalue = GraphicHandler::Update(nullptr, 30);
	GraphicHandler::CleanUp();

    return retvalue;
}