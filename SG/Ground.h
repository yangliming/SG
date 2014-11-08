#ifndef GROUND_H
#define GROUND_H

#include "SceneObject.h"
#include "Collideable.h"

class Ground : public SceneObject, public Collideable
{
public:
	Ground(float x, float y);
	virtual ~Ground();

	virtual void update(float totalticks, float deltaticks);

	virtual std::wstring description();

	virtual void setBounds();
private:
};

#endif // GROUND_H