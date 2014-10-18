#ifndef TEXTUREHANDLER_H
#define TEXTUREHANDLER_H

#include <map>
#include <d3d11_2.h>

#define TIID int

class TextureHandler
{
public:
	TextureHandler(ID3D11Device* device, ID3D11DeviceContext* context);
	~TextureHandler();

	TIID loadTexture(std::wstring filename);
	void releaseTexture(TIID id);

	ID3D11Resource* getResource(TIID id) const;
	ID3D11ShaderResourceView* getShaderResourceView(TIID id) const;
private:
	
	typedef struct
	{
		ID3D11Resource* TextureResource;
		ID3D11ShaderResourceView* ShaderResource;
	} TIID_DATA, *PTIID_DATA;

	std::map<TIID, TIID_DATA> m_data;
	std::map<std::wstring, TIID> m_names;
	
	ID3D11Device* m_d3dDevice;
	ID3D11DeviceContext* m_d3dContext;

	TIID m_nextID;
};

#endif // TEXTUREHANDLER_H