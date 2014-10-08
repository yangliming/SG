#ifndef GAMEITEM_H
#define GAMEITEM_H

#include <string>

class GameItem
{
public:
	std::wstring Type;

	GameItem(std::wstring type);
	~GameItem();

	virtual bool Use() = 0;
	virtual std::wstring Description() = 0;
	virtual std::wstring ToString();

	void DecrementCount();
	bool operator==(const GameItem& other);
	bool operator!=(const GameItem& other);
};

#endif // GAMEITEM_H