#include "GameObject.h"

GameObject::GameObject(int totalhp, int att, int def, std::wstring type,
	float x, float y, float z, float width, float height, bool draw, std::wstring filename)
	: DrawObject(x, y, z, width, height, draw, filename),
	  m_totalhp(totalhp), 
	  m_currenthp(totalhp), 
	  m_attack(att), 
	  m_defense(def), 
	  m_type(type),
	  m_canClean(false)
{
}

GameObject::~GameObject()
{
}

std::wstring GameObject::toString()
{
	return m_type;
}

bool GameObject::isCleanable()
{
	return m_canClean;
}