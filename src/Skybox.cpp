#include "../Inc/Skybox.h"

Skybox::Skybox()
{
	ID3D11Texture2D* SMTexture = 0;
	HR(DirectX::CreateDDSTextureFromFileEx(Device.Get(), L".dds", 0, D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, D3D11_RESOURCE_MISC_TEXTURECUBE, false, (ID3D11Resource**)&SMTexture, ShaderResourceView.GetAddressOf(), nullptr));
}


Skybox::~Skybox()
{
}