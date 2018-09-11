#pragma once
#include <Windows.h>
#include <string>

class WindowManager
{
public:
	WindowManager(HINSTANCE);
	virtual ~WindowManager();
	bool Initialize();
	int Run();
	virtual LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);

	int WindowWidth;
	int WindowHeight;
	std::wstring Title;

protected:
	HWND WindowHandle;
	HINSTANCE WinInstance;
};