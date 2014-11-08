#ifndef PLAYABLEUNIT_H
#define PLAYABLEUNIT_H

#include "GameObject.h"
#include "Collideable.h"

class PlayableUnit : public GameObject, public Collideable
{
public:
	PlayableUnit(int totalhp, int att, int def, std::wstring type);
	~PlayableUnit();

	virtual void action(float totalticks, float deltaticks);
	virtual std::wstring description();

	virtual void setBounds();
};

#endif // PLAYABLEUNIT_H