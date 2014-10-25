#include "Words.h"

Strength::Strength()
	: Word(L"Strength")
{
}

Strength::~Strength()
{
}

void Strength::action()
{

}

std::wstring Strength::description()
{
	return L"Adds attack damage";
}