#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <windows.h>
#include <d3d11.h>
#include <string>
#include "TextureHandler.h"

#define GHIID int

class DrawObject;

namespace GraphicHandler
{
	void Initialize(HINSTANCE hInstance);
	void ShowWindow(int nCmdShow);
	WPARAM Update(void (*Render)(void));
	void CleanUp();

	TIID LoadTexture(std::wstring filename);
	void RegisterDrawObject(DrawObject* obj);
	void UnRegisterDrawObject(DrawObject* obj);
}

#endif // GRAPHICS_H