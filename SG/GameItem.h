#ifndef GAMEITEM_H
#define GAMEITEM_H

#include <string>

class GameItem
{
public:
	std::wstring m_type;

	GameItem(std::wstring type);
	~GameItem();

	virtual bool use() = 0;
	virtual std::wstring description() = 0;
	virtual std::wstring toString();

	void decrementCount();
	bool operator==(const GameItem& other);
	bool operator!=(const GameItem& other);
};

#endif // GAMEITEM_H