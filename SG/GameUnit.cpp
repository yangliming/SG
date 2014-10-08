#include "GameUnit.h"

GameUnit::GameUnit(int totalhp, int att, int def, std::wstring type)
: TotalHp(totalhp), CurrentHp(totalhp), Attack(att), Defense(def), Type(type)
{
}

GameUnit::~GameUnit()
{
}

std::wstring GameUnit::ToString()
{
	return Type;
}

bool GameUnit::isDefeated()
{
	if (CurrentHp <= 0)
		return true;
	return false;
}