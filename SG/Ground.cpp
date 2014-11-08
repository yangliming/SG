#include "Ground.h"
#include "misc.h"

using namespace DirectX;

Ground::Ground(float x, float y)
	: SceneObject(L"ground", x, y, DEPTH_LVL_1, 500, 100, true, L"ground.bmp")
{
	setBounds();
}

Ground::~Ground()
{
}

void Ground::update(float totalticks, float deltaticks)
{
	
}

std::wstring Ground::description()
{
	return L"The ground!";
}

void Ground::setBounds()
{
	m_transform.x = this->getX();
	m_transform.y = this->getY();

	m_bounds.push_back(XMFLOAT2(0.0f, this->getHeight()));
	m_bounds.push_back(XMFLOAT2(this->getWidth(), this->getHeight()));
}