#include "DrawObject.h"
#include "GraphicHandler.h"

DrawObject::DrawObject(float x, float y, float z, float width, float height, bool draw, std::wstring filename)
	: m_filename(filename)
{
	m_drawValues.x = x;
	m_drawValues.y = y;
	m_drawValues.z = z;
	m_drawValues.width = width;
	m_drawValues.height = height;
	m_drawValues.draw = draw;
	m_drawValues.tIID = GraphicHandler::LoadTexture(filename);

	GraphicHandler::RegisterDrawObject(this);
}

DrawObject::~DrawObject()
{
	GraphicHandler::UnRegisterDrawObject(this);
}

PDRAWVALS DrawObject::GetDrawValues()
{
	return &m_drawValues;
}

void DrawObject::move(float x, float y, float z)
{
	m_drawValues.x += x;
	m_drawValues.y += y;
	m_drawValues.z += z;
}

void DrawObject::setX(float x)
{
	m_drawValues.x = x;
}

void DrawObject::setY(float y)
{
	m_drawValues.y = y;
}
void DrawObject::setZ(float z)
{
	m_drawValues.z = z;
}
void DrawObject::setWidth(float width)
{
	m_drawValues.width = width;
}
void DrawObject::setHeight(float height)
{
	m_drawValues.height = height;
}

void DrawObject::setDraw(bool draw)
{
	m_drawValues.draw = draw;
}

void DrawObject::setFilename(std::wstring filename)
{
	m_filename = filename;
	m_drawValues.tIID = GraphicHandler::LoadTexture(filename);
}

float DrawObject::getX() const
{
	return m_drawValues.x;
}

float DrawObject::getY() const
{
	return m_drawValues.y;
}

float DrawObject::getZ() const
{
	return m_drawValues.z;
}

float DrawObject::getWidth() const
{
	return m_drawValues.width;
}

float DrawObject::getHeight() const
{
	return m_drawValues.height;
}

bool DrawObject::getDraw() const
{
	return m_drawValues.draw;
}

std::wstring DrawObject::getFilename() const
{
	return m_filename;
}

