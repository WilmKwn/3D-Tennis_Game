#pragma once

#include <DirectXTex.h>

#include "Graphics.h"

class Texture
{
public:
	Texture(Graphics *graphics, const wchar_t* fullPath);
	~Texture();

	ID3D11ShaderResourceView *GetShaderResourceView();

private:
	ID3D11Resource *m_texture;
	ID3D11ShaderResourceView *m_shaderResourceView;
};