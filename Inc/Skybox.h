#pragma once
#include "../Inc/Result.h"
#include "../DirectXTK/Inc/DDSTextureLoader.h"
#include <d3d11.h>
#include <wrl.h>
#include <DirectXMath.h>
class Skybox
{
public:
	Skybox();
	~Skybox();
	Microsoft::WRL::ComPtr<ID3D11Device> Device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> DeviceContext;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> ShaderResourceView;
};