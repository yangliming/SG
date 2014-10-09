#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <d3d11.h>

class Texture
{
public:
	Texture(std::wstring filename, int x, int y, int zlevel, int width, int height, bool draw);
	~Texture();

	void setDraw(bool draw);
	void setX(int x);
	void setY(int y);
	void setZLevel(int zlevel);
	void setWidth(int width);
	void setHeight(int height);

	const std::wstring getFilename() const;
	bool getDraw() const;
	int getX() const;
	int getY() const;
	int getZLevel() const;
	int getWidth() const;
	int getHeight() const;
private:

	ID3D11Resource* m_data;
	ID3D11ShaderResourceView* m_shaderresourceview;

	std::wstring m_filename;
	int m_id;

	int m_x;
	int m_y;
	int m_zlevel;
	int m_width;
	int m_height;
	bool m_draw;

	void load();
};

#endif // TEXTURE_H