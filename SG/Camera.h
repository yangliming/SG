#ifndef CAMERA_H
#define CAMERA_H

#include <DirectXMath.h>

class Camera
{
public:
	Camera();
	~Camera();

	DirectX::XMMATRIX getMatrix();

	void setPosition(float x, float y, float z);
	void move(float x, float y, float z);
	void setViewParameters(DirectX::XMFLOAT3 eyePos, DirectX::XMFLOAT3 lookPos, DirectX::XMFLOAT3 upDir);
	void setOrthoProj(float width, float height, float nearZ, float farZ);
private:

	DirectX::XMFLOAT4X4 m_world;
	DirectX::XMFLOAT4X4 m_view;
	DirectX::XMFLOAT4X4 m_projection;
};

#endif // CAMERA_H