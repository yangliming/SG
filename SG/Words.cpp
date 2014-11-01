#include "Words.h"
#include "GameState.h"
#include "Explosion.h"

Strength::Strength()
	: Word(L"Strength")
{
}

Strength::~Strength()
{
}

void Strength::action()
{
	GameState::AddGameObject(new Explosion());
}

std::wstring Strength::description()
{
	return L"Adds attack damage";
}