#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <d3d11.h>

class Texture
{
public:
	Texture(std::wstring filename, int x, int y, int zlevel, int width, int height, bool draw);
	~Texture();

	void SetDraw(bool draw);
	void SetX(int x);
	void SetY(int y);
	void SetZLevel(int zlevel);
	void SetWidth(int width);
	void SetHeight(int height);

	const std::wstring GetFile() const;
	bool GetDraw() const;
	int GetX() const;
	int GetY() const;
	int GetZLevel() const;
	int GetWidth() const;
	int GetHeight() const;
private:

	ID3D11Resource* Data;
	ID3D11ShaderResourceView* ShaderResourceView;

	std::wstring Filename;
	int ID;

	int X;
	int Y;
	int ZLevel;
	int Width;
	int Height;
	bool Draw;

	void Load();
};

#endif // TEXTURE_H