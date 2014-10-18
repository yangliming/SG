#include "TextureHandler.h"
#include <string>
#include "DirectXTK\Inc\WICTextureLoader.h"
#include "misc.h"

TextureHandler::TextureHandler(ID3D11Device* device, ID3D11DeviceContext* context)
	: m_d3dDevice(device),
	  m_d3dContext(context),
	  m_nextID(0)
{
}

TextureHandler::~TextureHandler()
{
	auto iter = m_data.begin();
	while (iter != m_data.end())
	{
		SafeRelease(&(iter->second.TextureResource));
		SafeRelease(&(iter->second.ShaderResource));
		iter++;
	}
}

TIID TextureHandler::loadTexture(std::wstring filename)
{
	if (m_names.find(filename) != m_names.end())
		return m_names[filename];

	std::wstring path = L"Images/" + filename;
	ID3D11Resource* resource;
	ID3D11ShaderResourceView* shaderResourceView;

	DX::ThrowIfFailed(
		DirectX::CreateWICTextureFromFile(
			m_d3dDevice,
			m_d3dContext,
			path.data(),
			&resource,
			&shaderResourceView)
	);

	TIID_DATA data;
	data.TextureResource = resource;
	data.ShaderResource = shaderResourceView;

	m_data[m_nextID] = data;
	m_names[filename] = m_nextID;

	m_nextID++;
	return m_nextID - 1;
}

void TextureHandler::releaseTexture(TIID id)
{
	m_data.erase(id);

	auto iter = m_names.begin();
	while (iter != m_names.end())
	{
		if (iter->second == id)
		{
			m_names.erase(iter);
			return;
		}
	}
}

ID3D11Resource* TextureHandler::getResource(TIID id) const
{
	TIID_DATA data = m_data.at(id);
	return data.TextureResource;
}

ID3D11ShaderResourceView* TextureHandler::getShaderResourceView(TIID id) const
{
	TIID_DATA data = m_data.at(id);
	return data.ShaderResource;
}