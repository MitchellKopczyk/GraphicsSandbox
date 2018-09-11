#pragma once
#include <dinput.h>
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

#include "Result.h"

class Keyboard
{
public:
	Keyboard();
	~Keyboard();
	void Initialize(HINSTANCE hInstance, HWND hWnd);
	void GetState();
	bool KeyUp(byte) const;
	bool KeyDown(byte) const;
	bool KeyHeld(byte) const;
	bool KeyWasUp(byte) const;
	bool KeyWasDown(byte) const;

private:
	static const int numKeys = 256;
	LPDIRECTINPUT8 DirectInput;
	LPDIRECTINPUTDEVICE8 Device;
	byte CurrentKey[numKeys];
	byte LastKey[numKeys];
};