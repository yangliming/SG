#ifndef COLLIDEABLE_H
#define COLLIDEABLE_H

#include <list>
#include <DirectXMath.h>
#include "misc.h"

class Collideable
{
public:
	std::list<DirectX::XMFLOAT2> m_bounds;
	DirectX::XMFLOAT2 m_transform;

	virtual void setBounds() = 0;

	std::list<DirectX::XMFLOAT2> getBounds()
	{
		return m_bounds;
	}
private:
};

#endif // COLLIDEABLE_H