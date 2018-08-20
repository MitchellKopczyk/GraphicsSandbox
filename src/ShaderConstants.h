#pragma once
#include <DirectXMath.h>

struct cbPerObject
{
	DirectX::XMMATRIX  WVP;
	bool HasTexture;
};

