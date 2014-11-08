#ifndef GENERICSCENEOBJECT_H
#define GENERICSCENEOBJECT_H

#include "SceneObject.h"

class GenericSceneObject : public SceneObject
{
public:
	GenericSceneObject(std::wstring type, float x, float y, float z, float width, float height, bool draw, std::wstring filename);
	virtual ~GenericSceneObject();

	virtual void update(float totalticks, float deltaticks);

	virtual std::wstring description();
private:
};

#endif // GENERICSCENEOBJECT_H