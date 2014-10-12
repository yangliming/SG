#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "Global.h"
#include <windows.h>
#include <d3d11.h>
#include <string>

namespace GraphicHandler
{
	void Initialize(HINSTANCE hInstance);
	void ShowWindow(int nCmdShow);
	WPARAM Update(void (*Render)(void), int fps);
	void CleanUp();

	void InitScene();

	void LoadTexture(std::wstring filename, ID3D11Resource** texture, ID3D11ShaderResourceView** resource);
	int AddTexture(ID3D11ShaderResourceView* resource, int x, int y, int zlevel, int width, int height, bool draw);

	int AddText(std::wstring text);
	void RemoveText(int id);

	void RemoveTexture(int id);
	void ChangeTextureX(int id, int x);
	void ChangeTextureY(int id, int y);
	void ChangeTextureZLevel(int id, int zlevel);
	void ChangeTextureWidth(int id, int width);
	void ChangeTextureHeight(int id, int height);
	void ChangeTextureDraw(int id, bool draw);

}

#endif // GRAPHICS_H