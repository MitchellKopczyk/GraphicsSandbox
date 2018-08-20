#include "GraphicsManager.h"

GraphicsManager::GraphicsManager(HINSTANCE hInstance) : WindowManager(hInstance)
{
}

GraphicsManager::~GraphicsManager()
{
	if (ImmediateContext)ImmediateContext->ClearState();
}

Microsoft::WRL::ComPtr<ID3D11Device> GraphicsManager::GetDevice() const
{
	return Device;
}

Microsoft::WRL::ComPtr<ID3D11DeviceContext> GraphicsManager::GetImmediateContext() const
{
	return ImmediateContext;
}

void GraphicsManager::Initialize()
{
	WindowManager::Initialize();

	//Create Swap Chain
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(DXGI_SWAP_CHAIN_DESC));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = WindowWidth;
	sd.BufferDesc.Height = WindowHeight;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Numerator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = WindowHandle;
	sd.Windowed = true;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	HR(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0,
		0, 0, D3D11_SDK_VERSION, &sd, SwapChain.GetAddressOf(), Device.GetAddressOf(), 0, ImmediateContext.GetAddressOf()));

	//Create Render Targetview
	Microsoft::WRL::ComPtr<ID3D11Texture2D> BackBuffer;
	HR(SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(BackBuffer.GetAddressOf())));
	HR(Device->CreateRenderTargetView(BackBuffer.Get(), nullptr, RenderTargetView.GetAddressOf()));

	//Create Debth Stencil Buffer & View
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width = WindowWidth;
	depthStencilDesc.Height = WindowHeight;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	HR(Device->CreateTexture2D(&depthStencilDesc, 0, DepthStencilBuffer.GetAddressOf()));
	HR(Device->CreateDepthStencilView(DepthStencilBuffer.Get(), 0, DepthStencilView.GetAddressOf()));

	//Bind Render Target View and Debth Stencil View to the pipeline
	ImmediateContext->OMSetRenderTargets(1, RenderTargetView.GetAddressOf(), DepthStencilView.Get());

	//Set ViewPort
	Viewport.TopLeftX = 0;
	Viewport.TopLeftY = 0;
	Viewport.Width = static_cast<float>(WindowWidth);
	Viewport.Height = static_cast<float>(WindowHeight);
	Viewport.MinDepth = 0.0f;
	Viewport.MaxDepth = 1.0f;
	
	ImmediateContext->RSSetViewports(1, &Viewport);
	ImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

int GraphicsManager::Run()
{
	MSG msg = { 0 };

	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		Update();
		Draw();
	}
	return (int)msg.wParam;
}