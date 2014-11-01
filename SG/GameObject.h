#ifndef GAMEUNIT_H
#define GAMEUNIT_H

#include <string>
#include "DrawObject.h"

class GameObject : public DrawObject
{
public:
	int m_totalhp;
	int m_currenthp;
	int m_attack;
	int m_defense;
	bool m_canClean;
	std::wstring m_type;

	GameObject(int totalhp, int att, int def, std::wstring type,
		float x, float y, float z, float width, float height, bool draw, std::wstring filename);
	~GameObject();

	virtual void action(float totalticks, float deltaticks) = 0;
	virtual std::wstring description() = 0;
	virtual std::wstring toString();

	virtual bool isCleanable();
};

#endif // GAMEUNIT_H