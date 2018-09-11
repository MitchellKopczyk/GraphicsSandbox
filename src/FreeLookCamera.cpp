#include "../Inc/FreeLookCamera.h"

FreeLookCamera::FreeLookCamera(int height, int width)
{
	float x = float(height);
	float y = float(width);

	Position = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	Up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	Target = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	SetViewFrustrum(0.4f*3.14f, x / y, 0.1f, 10000.0f);
}

FreeLookCamera::~FreeLookCamera()
{
}

void FreeLookCamera::SetPosition(float x, float y, float z)
{
	Position = DirectX::XMVectorSet(x, y, z, 0.0f);
}

void FreeLookCamera::SetViewFrustrum(float fovY, float aspect, float nearZ, float farZ)
{
	FovY = fovY;
	Aspect = aspect;
	NearZ = nearZ;
	FarZ = farZ;

	Projection = DirectX::XMMatrixPerspectiveFovLH(FovY, Aspect, NearZ, FarZ);
}

void FreeLookCamera::UpdateViewMatrix()
{
	Rotation = DirectX::XMMatrixRotationRollPitchYaw(Pitch, Yaw, 0);
	Target = XMVector3Transform(DefaultForward, Rotation);
	Target = DirectX::XMVector3Normalize(Target);

	Right = XMVector3TransformCoord(DefaultRight, Rotation);
	Forward = XMVector3TransformCoord(DefaultForward, Rotation);
	Up = DirectX::XMVector3Cross(Forward, Right);
	Position = DirectX::XMVectorAdd(Position, DirectX::XMVectorScale(Right, MoveLeftRight));
	Position = DirectX::XMVectorAdd(Position, DirectX::XMVectorScale(Forward, MoveBackForward));

	MoveLeftRight = 0.0f;
	MoveBackForward = 0.0f;

	Target = DirectX::XMVectorAdd(Position, Target);

	View = DirectX::XMMatrixLookAtLH(Position, Target, Up);
}

DirectX::XMMATRIX FreeLookCamera::GetView() const
{
	return View;
}

DirectX::XMMATRIX FreeLookCamera::GetProjection() const
{
	return Projection;
}

DirectX::XMMATRIX FreeLookCamera::GetViewProjection() const
{
	return XMMatrixMultiply(GetView(), GetProjection());
}