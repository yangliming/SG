#include "PlayableUnit.h"

PlayableUnit::PlayableUnit(int totalhp, int att, int def, std::wstring type)
: GameUnit(totalhp, att, def, type, 0, 0, 0, 0, 0, false, L"")
{
	throw 3;
}

PlayableUnit::~PlayableUnit()
{
}