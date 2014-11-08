#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "DrawObject.h"

class SceneObject : public DrawObject
{
public:
	std::wstring m_type;
	bool m_canClean;

	SceneObject(std::wstring type, float x, float y, float z, float width, float height, bool draw, std::wstring filename);
	virtual ~SceneObject();

	virtual void update(float totalticks, float deltaticks) = 0;

	virtual std::wstring description() = 0;
	virtual std::wstring toString();

	virtual bool isCleanable();

private:
};

#endif // SCENEOBJECT_H