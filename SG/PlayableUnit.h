#ifndef PLAYABLEUNIT_H
#define PLAYABLEUNIT_H

#include "GameObject.h"

class PlayableUnit : public GameObject
{
public:
	PlayableUnit(int totalhp, int att, int def, std::wstring type);
	~PlayableUnit();

	virtual void action(float totalticks, float deltaticks);
	virtual std::wstring description();
};

#endif // PLAYABLEUNIT_H