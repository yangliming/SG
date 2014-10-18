#include "Camera.h"

using namespace DirectX;

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::setPosition(float x, float y, float z)
{
	XMStoreFloat4x4(&m_world, XMMatrixTranslation(x, y, z));
}

void Camera::move(float x, float y, float z)
{
	XMStoreFloat4x4(&m_world, XMLoadFloat4x4(&m_world) * XMMatrixTranslation(x, y, z));
}

void Camera::setViewParameters(XMFLOAT3 eyePos, XMFLOAT3 lookPos, XMFLOAT3 upDir)
{
	XMVECTOR eye = XMVectorSet(eyePos.x, eyePos.y, eyePos.z, 0.0f);
	XMVECTOR look = XMVectorSet(lookPos.x, lookPos.y, lookPos.z, 0.0f);
	XMVECTOR up = XMVectorSet(upDir.x, upDir.y, upDir.z, 0.0f);

	XMStoreFloat4x4(&m_view, XMMatrixLookAtLH(eye, look, up));
}

void Camera::setOrthoProj(float width, float height, float nearZ, float farZ)
{
	XMStoreFloat4x4(&m_projection, XMMatrixOrthographicLH(width, height, nearZ, farZ));
}

XMMATRIX Camera::getMatrix()
{
	XMMATRIX world = XMLoadFloat4x4(&m_world);
	XMMATRIX view = XMLoadFloat4x4(&m_view);
	XMMATRIX proj = XMLoadFloat4x4(&m_projection);

	XMMATRIX wvp = world * view * proj;
	return XMMatrixTranspose(wvp);
}