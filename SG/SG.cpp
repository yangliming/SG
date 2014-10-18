#include <windows.h>
#include <windowsx.h>

#include "Global.h"
#include "GraphicHandler.h"
#include "Texture.h"
#include "DrawObject.h"

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
	GraphicHandler::Initialize(hInstance);
	GraphicHandler::ShowWindow(nCmdShow);

	DrawObject obj(-5, -4, 0, 9, 9, true, L"grass.bmp");
	DrawObject obj2(-3, -2, 0, 4, 4, true, L"grass.bmp");

	WPARAM retvalue = GraphicHandler::Update(nullptr, 30);
	GraphicHandler::CleanUp();
    return retvalue;
}