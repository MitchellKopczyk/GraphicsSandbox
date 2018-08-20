#include "WindowManager.h"

namespace
{
	WindowManager* WinPtr = nullptr;
}

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return WinPtr->MsgProc(hwnd, msg, wParam, lParam);
}

LRESULT WindowManager::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

WindowManager::WindowManager(HINSTANCE hInstance)
{
	WinInstance = hInstance;
	WindowHandle = 0;
	WinPtr = this;
}

WindowManager::~WindowManager()
{
}

bool WindowManager::Initialize()
{
	WNDCLASS wc;
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = WinInstance;
	wc.lpfnWndProc = MainWndProc;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"WindowApplication";

	if (!RegisterClass(&wc))
		return false;

	WindowHandle = CreateWindow(L"WindowApplication", Title.c_str(),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WindowWidth, WindowHeight, 0, 0, WinInstance, 0);
	if (!WindowHandle)
		return false;

	ShowWindow(WindowHandle, SW_SHOW);
	return true;
}

int WindowManager::Run()
{
	MSG msg = { 0 };

	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;
}
