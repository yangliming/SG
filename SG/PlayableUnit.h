#ifndef PLAYABLEUNIT_H
#define PLAYABLEUNIT_H

#include "GameUnit.h"

class PlayableUnit : GameUnit
{
public:
	PlayableUnit(int totalhp, int att, int def, std::wstring type);
	~PlayableUnit();

	virtual void action() = 0;
	virtual std::wstring description() = 0;
};

#endif // PLAYABLEUNIT_H