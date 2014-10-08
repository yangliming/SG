#include "GameItem.h"

GameItem::GameItem(std::wstring type)
: Type(type)
{
}

GameItem::~GameItem()
{
}

std::wstring GameItem::ToString()
{
	return Type;
}

bool GameItem::operator==(const GameItem& other)
{
	if (Type == other.Type)
		return true;
	return false;
}

bool GameItem::operator!=(const GameItem& other)
{
	if (Type == other.Type)
		return false;
	return true;
}

void GameItem::DecrementCount()
{
	throw 1;
}