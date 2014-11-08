#include "SceneObject.h"

SceneObject::SceneObject(std::wstring type, float x, float y, float z, float width, float height, bool draw, std::wstring filename)
	: DrawObject(x, y, z, width, height, draw, filename),
	m_type(type),
	m_canClean(false)
{
}

SceneObject::~SceneObject()
{
}

std::wstring SceneObject::toString()
{
	return m_type;
}

bool SceneObject::isCleanable()
{
	return m_canClean;
}