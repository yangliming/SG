#ifndef GAMEUNIT_H
#define GAMEUNIT_H

#include <string>

class GameUnit
{
public:
	int m_totalhp;
	int m_currenthp;
	int m_attack;
	int m_defense;
	std::wstring m_type;

	GameUnit(int totalhp, int att, int def, std::wstring type);
	~GameUnit();

	virtual void action() = 0;
	virtual std::wstring description() = 0;
	virtual std::wstring toString();

	virtual bool isDefeated();
};

#endif // GAMEUNIT_H