#ifndef PLAYABLEUNIT_H
#define PLAYABLEUNIT_H

#include "GameUnit.h"

class PlayableUnit : public GameUnit
{
public:
	PlayableUnit(int totalhp, int att, int def, std::wstring type);
	~PlayableUnit();

	virtual void action();
	virtual std::wstring description();
};

#endif // PLAYABLEUNIT_H