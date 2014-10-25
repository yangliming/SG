#include "GameItem.h"

GameItem::GameItem(std::wstring type)
	: m_type(type)
{
}

GameItem::~GameItem()
{
}

std::wstring GameItem::toString()
{
	return m_type;
}

bool GameItem::operator==(const GameItem& other)
{
	if (m_type == other.m_type)
		return true;
	return false;
}

bool GameItem::operator!=(const GameItem& other)
{
	if (m_type == other.m_type)
		return false;
	return true;
}

void GameItem::decrementCount()
{
	throw 1;
}