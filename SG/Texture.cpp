#include "Texture.h"
#include "GraphicHandler.h"

Texture::Texture(std::wstring filename, int x, int y, int zlevel, int width, int height, bool draw)
	: m_x(x), m_y(y), m_zlevel(zlevel), m_width(width), m_height(height), m_draw(draw)
{
	m_filename = L"Images/" + filename;
	load();
	m_id = GraphicHandler::AddTexture(m_shaderresourceview, m_x, m_y, m_zlevel, m_width, m_height, m_draw);
}

Texture::~Texture()
{
	GraphicHandler::RemoveTexture(m_id);
	if (m_data != NULL)
		m_data->Release();
	if (m_shaderresourceview != NULL)
		m_shaderresourceview->Release();
}

void Texture::setDraw(bool draw)
{
	m_draw = draw;
	GraphicHandler::ChangeTextureDraw(m_id, draw);
}

void Texture::setX(int x)
{
	m_x = x;
	GraphicHandler::ChangeTextureX(m_id, x);
}

void Texture::setY(int y)
{
	m_y = y;
	GraphicHandler::ChangeTextureY(m_id, y);
}

void Texture::setZLevel(int zlevel)
{
	m_zlevel = zlevel;
	GraphicHandler::ChangeTextureZLevel(m_id, zlevel);
}

void Texture::setWidth(int width)
{
	m_width = width;
	GraphicHandler::ChangeTextureWidth(m_id, width);
}

void Texture::setHeight(int height)
{
	m_height = height;
	GraphicHandler::ChangeTextureHeight(m_id, height);
}

const std::wstring Texture::getFilename() const
{
	return m_filename;
}

bool Texture::getDraw() const
{
	return m_draw;
}

int Texture::getX() const
{
	return m_x;
}

int Texture::getY() const
{
	return m_y;
}

int Texture::getZLevel() const
{
	return m_zlevel;
}

int Texture::getWidth() const
{
	return m_width;
}

int Texture::getHeight() const
{
	return m_height;
}

void Texture::load()
{
	if (m_data != NULL)
		m_data->Release();
	if (m_shaderresourceview != NULL)
		m_shaderresourceview->Release();

	GraphicHandler::LoadTexture(m_filename, &m_data, &m_shaderresourceview);
}