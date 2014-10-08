#ifndef GAMEUNIT_H
#define GAMEUNIT_H

#include <string>

class GameUnit
{
public:
	int TotalHp;
	int CurrentHp;
	int Attack;
	int Defense;
	std::wstring Type;

	GameUnit(int totalhp, int att, int def, std::wstring type);
	~GameUnit();

	virtual void Action() = 0;
	virtual std::wstring Description() = 0;
	virtual std::wstring ToString();

	virtual bool isDefeated();
};

#endif // GAMEUNIT_H