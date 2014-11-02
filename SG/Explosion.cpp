#include "Explosion.h"
#include "GameState.h"
#include "misc.h"

Explosion::Explosion()
	: GameObject(0, 0, 0, L"Explosion", 10, 10, DEPTH_LVL_0, 100, 100, true, L"explosion0.png"),
	m_start(-1.0f)
{
	this->setFilename(L"explosion1.png");
	this->setFilename(L"explosion2.png");
	this->setFilename(L"explosion3.png");
	this->setFilename(L"explosion0.png");
}

Explosion::~Explosion()
{
}

void Explosion::action(float totalticks, float deltaticks)
{
	if (m_start == -1.0f)
		m_start = totalticks;

	float dt = totalticks - m_start;

	if (dt < 10)
		this->setFilename(L"explosion0.png");
	else if (dt < 20)
		this->setFilename(L"explosion1.png");
	else if (dt < 30)
		this->setFilename(L"explosion2.png");
	else if (dt < 40)
		this->setFilename(L"explosion3.png");
	else
	{
		this->setDraw(false);
		this->m_canClean = true;
	}
}

std::wstring Explosion::description()
{
	return L"An explosion!";
}