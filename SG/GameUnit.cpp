#include "GameUnit.h"

GameUnit::GameUnit(int totalhp, int att, int def, std::wstring type)
: m_totalhp(totalhp), m_currenthp(totalhp), m_attack(att), m_defense(def), m_type(type)
{
}

GameUnit::~GameUnit()
{
}

std::wstring GameUnit::toString()
{
	return m_type;
}

bool GameUnit::isDefeated()
{
	if (m_currenthp <= 0)
		return true;
	return false;
}