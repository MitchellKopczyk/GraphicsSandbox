#pragma once
#include <DirectXMath.h>
#include <d3d11.h>
#include <Windows.h>
#include <wrl.h>
#pragma comment(lib, "d3d11.lib")

#include "Result.h"

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

class Cube
{
public:
	Cube();
	void Create(ID3D11Device*);
	void DrawCube(ID3D11DeviceContext*);
	void SetBuffers(ID3D11DeviceContext*);
	~Cube();
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> VertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> IndexBuffer;
};