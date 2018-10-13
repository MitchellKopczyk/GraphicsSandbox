#include "../Inc/Material.h"

Material::Material(Model& model, aiMaterial* material, ID3D11Device* Device, ID3D11DeviceContext* DeviceContext)
{
	aiString StringBuffer;
	aiColor4D color;
	float scalar;

	if (AI_SUCCESS == material->Get(AI_MATKEY_NAME, StringBuffer))
		Name = StringBuffer.C_Str();

	if (AI_SUCCESS == aiGetMaterialTexture(material, aiTextureType_DIFFUSE, 0, &StringBuffer))
		TextureMapFiles.insert(std::pair<TextureMapTypes, std::string>(TextureMapTypes::DiffuseMap, StringBuffer.C_Str()));

	if (AI_SUCCESS == aiGetMaterialTexture(material, aiTextureType_AMBIENT, 0, &StringBuffer))
		TextureMapFiles.insert(std::pair<TextureMapTypes, std::string>(TextureMapTypes::AmbientMap, StringBuffer.C_Str()));

	if (AI_SUCCESS == aiGetMaterialTexture(material, aiTextureType_SPECULAR, 0, &StringBuffer))
		TextureMapFiles.insert(std::pair<TextureMapTypes, std::string>(TextureMapTypes::SpecularMap, StringBuffer.C_Str()));

	if (AI_SUCCESS == material->Get(AI_MATKEY_COLOR_DIFFUSE, color))
		MaterialCompoents.insert(std::pair<MaterialColors, DirectX::XMFLOAT4>(MaterialColors::Diffuse, DirectX::XMFLOAT4(reinterpret_cast<const float*>(&color))));

	if (AI_SUCCESS == material->Get(AI_MATKEY_COLOR_SPECULAR, color))
		MaterialCompoents.insert(std::pair<MaterialColors, DirectX::XMFLOAT4>(MaterialColors::Specular, DirectX::XMFLOAT4(reinterpret_cast<const float*>(&color))));

	if (AI_SUCCESS == material->Get(AI_MATKEY_COLOR_AMBIENT, color))
		MaterialCompoents.insert(std::pair<MaterialColors, DirectX::XMFLOAT4>(MaterialColors::Ambient, DirectX::XMFLOAT4(reinterpret_cast<const float*>(&color))));

	if (AI_SUCCESS == material->Get(AI_MATKEY_OPACITY, scalar))
		Scalars.insert(std::pair<MaterialScalars, float>(MaterialScalars::Opacity, scalar));

	if (AI_SUCCESS == material->Get(AI_MATKEY_SHININESS, scalar))
	{
		scalar *= .25f;
		Scalars.insert(std::pair<MaterialScalars, float>(MaterialScalars::Shininess, scalar));
	}

	//Needs to be moved to own function
	std::string preparedString = "./Models/windmill_obj/";
	std::map<TextureMapTypes, std::string>::iterator it = this->TextureMapFiles.find(TextureMapTypes::DiffuseMap);
	if (it != this->TextureMapFiles.end())
	{
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> ShaderResourceView;
		Microsoft::WRL::ComPtr<ID3D11Resource> Resource;
		preparedString += it->second;
		std::wstring widestr = std::wstring(preparedString.begin(), preparedString.end());
		const wchar_t* widecstr = widestr.c_str();
		HR(DirectX::CreateWICTextureFromFile(Device, widecstr, &Resource, &ShaderResourceView));
		TextureBuffers.insert(std::pair<TextureMapTypes, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>>(TextureMapTypes::DiffuseMap, ShaderResourceView));
	}

	Microsoft::WRL::ComPtr<ID3D11SamplerState> SamplerState;
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	HR(Device->CreateSamplerState(&sampDesc, &SamplerState));
	DeviceContext->PSSetSamplers(0, 1, &SamplerState);
}

Material::~Material()
{
}