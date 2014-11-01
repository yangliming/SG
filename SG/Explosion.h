#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "GameObject.h"

class Explosion : public GameObject
{
public:
	Explosion();
	~Explosion();

	virtual void action(float totalticks, float deltaticks);
	virtual std::wstring description();
	
private:

	float m_start;
};

#endif // EXPLOSION_H