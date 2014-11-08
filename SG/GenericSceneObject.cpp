#include "GenericSceneObject.h"

GenericSceneObject::GenericSceneObject(std::wstring type, float x, float y, float z, float width, float height, bool draw, std::wstring filename)
	: SceneObject(type, x, y, z, width, height, draw, filename)
{
}

GenericSceneObject::~GenericSceneObject()
{
}

void GenericSceneObject::update(float totalticks, float deltaticks)
{
}

std::wstring GenericSceneObject::description()
{
	return L"Generic Scene Object";
}