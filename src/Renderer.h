#pragma once
#include "GraphicsManager.h"
#include "FreeLookCamera.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Result.h"

#include "VertexLayout.h"
#include "ShaderConstants.h"
#include "Model.h"

class WaveFrontModel;

class Renderer : public GraphicsManager
{
public:
	Renderer(HINSTANCE hInstance);
	~Renderer();
	void Initalize();
	void Update();
	void HandleUserInput();
	void Draw();
	void BuildShaders();
	void BuildInputLayout();
	void BuildShaderConstants();

private:
	//COM Objects
	Microsoft::WRL::ComPtr<ID3D11VertexShader> VertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> PixelShader;
	Microsoft::WRL::ComPtr<ID3D10Blob> VertexBlob;
	Microsoft::WRL::ComPtr<ID3D10Blob> PixelBlob;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> InputLayout;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> WireFrame;
	
	//Camera 
	cbPerObject cbPerObj;
	Microsoft::WRL::ComPtr<ID3D11Buffer> cbPerObjectBuffer;
	//FrameWork Objects
	FreeLookCamera* PrimaryCamera;
	Keyboard* UserKeyboard;
	Mouse* UserMouse;
	Model* ObjModelUno;	
};