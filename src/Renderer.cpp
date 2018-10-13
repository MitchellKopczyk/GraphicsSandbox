#include "../Inc/Renderer.h"

void Renderer::Initalize()
{
	GraphicsManager::Initialize();
	BuildShaders();
	BuildShaderConstants();
	BuildInputLayout();
	if (!ObjModelUno->Load("./Models/windmill_obj/windmill.obj", Device.Get(), ImmediateContext.Get()))
		MessageBox(0, L"Failed to Load Model", 0, 0);
	UserKeyboard->Initialize(WinInstance, WindowHandle);
	UserMouse->Initialize(WinInstance, WindowHandle);
}


void Renderer::BuildShaders()
{
	HR(D3DCompileFromFile(L"./Shaders/VertexShader.hlsl", 0, 0, "main", "vs_5_0", 0, 0, VertexBlob.GetAddressOf(), 0));
	HR(D3DCompileFromFile(L"./Shaders/PixelShader.hlsl", 0, 0, "main", "ps_5_0", 0, 0, PixelBlob.GetAddressOf(), 0));
	HR(Device->CreateVertexShader(VertexBlob->GetBufferPointer(), VertexBlob->GetBufferSize(), NULL, VertexShader.GetAddressOf()));
	HR(Device->CreatePixelShader(PixelBlob->GetBufferPointer(), PixelBlob->GetBufferSize(), NULL, PixelShader.GetAddressOf()));
}

void Renderer::BuildInputLayout()
{
	D3D11_INPUT_ELEMENT_DESC InputLayoutDescription[] =
	{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	UINT numElements = ARRAYSIZE(InputLayoutDescription);
	HR(Device->CreateInputLayout(InputLayoutDescription, numElements, VertexBlob->GetBufferPointer(), VertexBlob->GetBufferSize(), InputLayout.GetAddressOf()));
	ImmediateContext->IASetInputLayout(InputLayout.Get());
}

void Renderer::BuildShaderConstants()
{
	D3D11_BUFFER_DESC cbbd;

	//PerObject
	ZeroMemory(&cbbd, sizeof(D3D11_BUFFER_DESC));
	cbbd.Usage = D3D11_USAGE_DEFAULT;
	cbbd.ByteWidth = sizeof(cbPerObject);
	cbbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbbd.CPUAccessFlags = 0;
	cbbd.MiscFlags = 0;
	HR(Device->CreateBuffer(&cbbd, NULL, cbPerObjectBuffer.GetAddressOf()));
}

void Renderer::Update()
{
	HandleUserInput();
	ImmediateContext->VSSetShader(VertexShader.Get(), 0, 0);
	ImmediateContext->PSSetShader(PixelShader.Get(), 0, 0);
	DirectX::XMMATRIX World = DirectX::XMMatrixIdentity();
	DirectX::XMMATRIX WVP = World * PrimaryCamera->GetViewProjection();
	cbPerObj.WVP = DirectX::XMMatrixTranspose(WVP);
	ImmediateContext->UpdateSubresource(cbPerObjectBuffer.Get(), 0, NULL, &cbPerObj, 0, 0);
	ImmediateContext->VSSetConstantBuffers(0, 1, cbPerObjectBuffer.GetAddressOf());
}

void Renderer::Draw()
{
	float Black[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	ImmediateContext->ClearRenderTargetView(RenderTargetView.Get(), Black);
	ImmediateContext->ClearDepthStencilView(DepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	ObjModelUno->Draw(ImmediateContext.Get());
	SwapChain->Present(0, 0);
}

void Renderer::HandleUserInput()
{
	const float WASDSpeed = .1f;
	UserKeyboard->GetState();
	UserMouse->GetState();

	if (UserMouse->ChangedPosition())
	{
		PrimaryCamera->Yaw += UserMouse->GetCurrentStateX() * 0.0015f;
		PrimaryCamera->Pitch += UserMouse->GetCurrentStateY()* 0.0015f;
		UserMouse->SetLastState(UserMouse->GetCurrentState());
	}

	if (UserKeyboard->KeyDown(DIK_N))
	{
		D3D11_RASTERIZER_DESC wfdesc;
		ZeroMemory(&wfdesc, sizeof(D3D11_RASTERIZER_DESC));
		wfdesc.FillMode = D3D11_FILL_WIREFRAME;
		wfdesc.CullMode = D3D11_CULL_NONE;
		Device->CreateRasterizerState(&wfdesc, &WireFrame);
		ImmediateContext->RSSetState(WireFrame.Get());
		MessageBox(0, L"WireFrame Enabled", 0, 0);
	}

	if (UserKeyboard->KeyDown(DIK_M))
	{
		D3D11_RASTERIZER_DESC wfdesc;
		ZeroMemory(&wfdesc, sizeof(D3D11_RASTERIZER_DESC));
		wfdesc.CullMode = D3D11_CULL_NONE;
		Device->CreateRasterizerState(&wfdesc, &WireFrame);
		ImmediateContext->RSSetState(WireFrame.Get());
		MessageBox(0, L"WireFrame Disabled", 0, 0);
	}

	if (UserKeyboard->KeyDown(DIK_W))
		PrimaryCamera->MoveBackForward += WASDSpeed;

	if (UserKeyboard->KeyDown(DIK_A))
		PrimaryCamera->MoveLeftRight -= WASDSpeed;

	if (UserKeyboard->KeyDown(DIK_S))
		PrimaryCamera->MoveBackForward -= WASDSpeed;

	if (UserKeyboard->KeyDown(DIK_D))
		PrimaryCamera->MoveLeftRight += WASDSpeed;

	PrimaryCamera->UpdateViewMatrix();
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	std::shared_ptr<Renderer> Scene = std::shared_ptr<Renderer>(new Renderer(hInstance));
	Scene->WindowHeight = 800;
	Scene->WindowWidth = 1200;

	Scene->Initalize();
	Scene->Run();
}

Renderer::Renderer(HINSTANCE hInstance) : GraphicsManager(hInstance)
{
	PrimaryCamera = new FreeLookCamera(WindowHeight, WindowWidth);
	PrimaryCamera->SetPosition(0.0f, 500.0f, -2000.0f);
	UserKeyboard = new Keyboard();
	UserMouse = new Mouse();
	ObjModelUno = new Model();
}

Renderer::~Renderer()
{
	delete PrimaryCamera;
	delete UserKeyboard;
	delete UserMouse;
	delete ObjModelUno;
}