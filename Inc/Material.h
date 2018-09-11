#pragma once
#include "ModelDependencies.h"
class Material
{
	friend class Model;
public:
	Material(Model&, aiMaterial*, ID3D11Device*, ID3D11DeviceContext*);
	~Material();

	//Texure Maps
	std::string Name;
	std::map<TextureMapTypes, std::string> TextureMapFiles;
	std::map<TextureMapTypes, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> TextureBuffers;

	//Material Compoenents
	std::map<MaterialColors, DirectX::XMFLOAT4> MaterialCompoents;
	std::map<MaterialScalars, float> Scalars;
};