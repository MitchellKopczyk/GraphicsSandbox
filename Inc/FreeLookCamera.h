#pragma once
#include <DirectXMath.h>

class FreeLookCamera
{
public:
	FreeLookCamera(int, int);
	~FreeLookCamera();
	void SetPosition(float, float, float);
	void SetViewFrustrum(float, float, float, float);
	void UpdateViewMatrix();


	DirectX::XMMATRIX GetView() const;
	DirectX::XMMATRIX GetProjection() const;
	DirectX::XMMATRIX GetViewProjection() const;
	DirectX::XMVECTOR GetPositon() const;

	//Rotation around the y-axis
	float Yaw = 0.0f;
	//Rotation around the x-axis
	float Pitch = 0.0f;
	float MoveLeftRight = 0.0f;
	float MoveBackForward = 0.0f;

private:
	DirectX::XMVECTOR Position;
	DirectX::XMVECTOR Up;
	DirectX::XMVECTOR Right;
	DirectX::XMVECTOR Target; // Always Unit Vector
	DirectX::XMVECTOR Forward;

	const DirectX::XMVECTOR DefaultForward = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	const DirectX::XMVECTOR DefaultRight = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

	float NearZ;
	float FarZ;
	float Aspect;
	float FovY;
	float NearWindowHeight;
	float FarWindowHeight;

	DirectX::XMMATRIX Rotation;
	DirectX::XMMATRIX View;
	DirectX::XMMATRIX Projection;
};