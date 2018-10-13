#pragma once
#include "../Inc/VertexLayout.h"
#include "../Inc/Result.h"

#include <d3d11.h>
#include <wrl.h>
#include <DirectXMath.h>
#include <vector>
#define M_PI 3.14159265358979323846

class Sphere
{
public:
	Sphere(ID3D11Device*, ID3D11DeviceContext*);
	~Sphere();
	unsigned int IndiciesCount;
	void Generate(double, double, double);
	void Draw();
private:
	Microsoft::WRL::ComPtr<ID3D11Device> Device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> DeviceContext;
	Microsoft::WRL::ComPtr<ID3D11Buffer> VertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> IndexBuffer;
};