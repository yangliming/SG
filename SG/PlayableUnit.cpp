#include "PlayableUnit.h"

PlayableUnit::PlayableUnit(int totalhp, int att, int def, std::wstring type)
	: GameObject(totalhp, att, def, type,
	  0, 0, 0, 80, 100, true, L"person.png")
{
}

PlayableUnit::~PlayableUnit()
{
}

void PlayableUnit::action(float totalticks, float deltaticks)
{

}

std::wstring PlayableUnit::description()
{
	throw 3;
}