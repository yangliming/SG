#include "Texture.h"
#include "GraphicHandler.h"

Texture::Texture(std::wstring filename, int x, int y, int zlevel, int width, int height, bool draw)
	: X(x), Y(y), ZLevel(zlevel), Width(width), Height(height), Draw(draw)
{
	Filename = L"Images/" + filename;
	Load();
	ID = GraphicHandler::AddTexture(ShaderResourceView, X, Y, ZLevel, Width, Height, Draw);
}

Texture::~Texture()
{
	GraphicHandler::RemoveTexture(ID);
	if (Data != NULL)
		Data->Release();
	if (ShaderResourceView != NULL)
		ShaderResourceView->Release();
}

void Texture::SetDraw(bool draw)
{
	Draw = draw;
	GraphicHandler::ChangeTextureDraw(ID, draw);
}

void Texture::SetX(int x)
{
	X = x;
	GraphicHandler::ChangeTextureX(ID, x);
}

void Texture::SetY(int y)
{
	Y = y;
	GraphicHandler::ChangeTextureY(ID, y);
}

void Texture::SetZLevel(int zlevel)
{
	ZLevel = zlevel;
	GraphicHandler::ChangeTextureZLevel(ID, zlevel);
}

void Texture::SetWidth(int width)
{
	Width = width;
	GraphicHandler::ChangeTextureWidth(ID, width);
}

void Texture::SetHeight(int height)
{
	Height = height;
	GraphicHandler::ChangeTextureHeight(ID, height);
}

const std::wstring Texture::GetFile() const
{
	return Filename;
}

bool Texture::GetDraw() const
{
	return Draw;
}

int Texture::GetX() const
{
	return X;
}

int Texture::GetY() const
{
	return Y;
}

int Texture::GetZLevel() const
{
	return ZLevel;
}

int Texture::GetWidth() const
{
	return Width;
}

int Texture::GetHeight() const
{
	return Height;
}

void Texture::Load()
{
	if (Data != NULL)
		Data->Release();
	if (ShaderResourceView != NULL)
		ShaderResourceView->Release();

	GraphicHandler::LoadTexture(Filename, &Data, &ShaderResourceView);
}