#include "PlayableUnit.h"

PlayableUnit::PlayableUnit(int totalhp, int att, int def, std::wstring type)
: GameUnit(totalhp, att, def, type)
{
}

PlayableUnit::~PlayableUnit()
{
}