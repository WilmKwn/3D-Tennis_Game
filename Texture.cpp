#include "Texture.h"

Texture::Texture(Graphics *graphics, const wchar_t* fullPath)
{
	DirectX::ScratchImage imageData;
	DirectX::LoadFromWICFile(fullPath, DirectX::WIC_FLAGS_NONE, NULL, imageData);
	DirectX::CreateTexture(graphics->GetDevice(), imageData.GetImages(), imageData.GetImageCount(), imageData.GetMetadata(), &m_texture);

	D3D11_SHADER_RESOURCE_VIEW_DESC shaderDesc = {};
	shaderDesc.Format = imageData.GetMetadata().format;
	shaderDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderDesc.Texture2D.MipLevels = (UINT)imageData.GetMetadata().mipLevels;
	shaderDesc.Texture2D.MostDetailedMip = 0;

	graphics->GetDevice()->CreateShaderResourceView(m_texture, &shaderDesc, &m_shaderResourceView);
}

Texture::~Texture()
{
	if (m_texture) m_texture->Release();
	if (m_shaderResourceView) m_shaderResourceView->Release();
}

ID3D11ShaderResourceView *Texture::GetShaderResourceView()
{
	return m_shaderResourceView;
}