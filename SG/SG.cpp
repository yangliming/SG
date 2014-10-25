#include <windows.h>
#include <windowsx.h>

#include "Global.h"
#include "GraphicHandler.h"
#include "GameState.h"

void RenderUpdate();

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
	GraphicHandler::Initialize(hInstance);
	GameState::Initialize();
	GraphicHandler::ShowWindow(nCmdShow);
	
	WPARAM retvalue = GraphicHandler::Update(RenderUpdate);

	GameState::CleanUp();
	GraphicHandler::CleanUp();
    return retvalue;
}

void RenderUpdate()
{
	GameState::Update();
}