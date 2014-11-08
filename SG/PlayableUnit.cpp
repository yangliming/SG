#include "PlayableUnit.h"
#include "misc.h"

using namespace DirectX;

PlayableUnit::PlayableUnit(int totalhp, int att, int def, std::wstring type)
	: GameObject(totalhp, att, def, type,
	  0, 0, DEPTH_LVL_1, 80, 100, true, L"person.png")
{
	setBounds();
}

PlayableUnit::~PlayableUnit()
{
}

void PlayableUnit::action(float totalticks, float deltaticks)
{
	m_transform.x = this->getX();
	m_transform.y = this->getY();
}

std::wstring PlayableUnit::description()
{
	throw 3;
}

void PlayableUnit::setBounds()
{
	m_bounds.push_back(XMFLOAT2(0.0f, 0.0f));
	m_bounds.push_back(XMFLOAT2(this->getWidth(), 0.0f));
	m_bounds.push_back(XMFLOAT2(this->getWidth(), this->getHeight()));
	m_bounds.push_back(XMFLOAT2(0.0f, this->getHeight()));
}