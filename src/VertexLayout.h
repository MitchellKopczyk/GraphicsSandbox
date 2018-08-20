#pragma once
#include <DirectXMath.h>
#include <d3d11.h>

struct Vertex	
{
	Vertex() {}
	Vertex(float x, float y, float z,
		float u, float v,
		float nx, float ny, float nz)
		: Position(x, y, z), texCoord(u, v), Normal(nx, ny, nz) {}

	DirectX::XMFLOAT3 Position;
	DirectX::XMFLOAT2 texCoord;
	DirectX::XMFLOAT3 Normal;
};