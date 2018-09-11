#pragma once
#include "WindowManager.h"
#include <d3d11.h>
#include <wrl.h>
#include "Result.h"

#pragma comment(lib, "d3d11.lib")

class GraphicsManager : public WindowManager
{
public:
	GraphicsManager(HINSTANCE);
	virtual ~GraphicsManager();
	void Initialize();
	virtual void Update() = 0;
	virtual void Draw() = 0;
	int Run();

	Microsoft::WRL::ComPtr<ID3D11Device> GetDevice() const;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> GetImmediateContext() const;

protected:
	Microsoft::WRL::ComPtr<ID3D11Device> Device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> ImmediateContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> SwapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> RenderTargetView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> DepthStencilBuffer;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> DepthStencilView;

	D3D11_VIEWPORT Viewport;
};