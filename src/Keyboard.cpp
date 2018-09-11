#include "../Inc/Keyboard.h"

Keyboard::Keyboard()
{
	DirectInput = 0;
	Device = 0;
}

Keyboard::~Keyboard()
{
	if (Device != 0)
	{
		Device->Unacquire();
		Device->Release();
		Device = 0;
	}
}

void Keyboard::Initialize(HINSTANCE hInstance, HWND hWnd)
{
	HR(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&DirectInput, NULL));
	HR(DirectInput->CreateDevice(GUID_SysKeyboard, &Device, 0));
	HR(Device->SetDataFormat(&c_dfDIKeyboard));
	HR(Device->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	HR(Device->Acquire());
}

void Keyboard::GetState()
{
	if (Device != 0)
	{
		memcpy(LastKey, CurrentKey, sizeof(CurrentKey));

		if (FAILED(Device->GetDeviceState(sizeof(CurrentKey), (LPVOID)CurrentKey)))
		{
			if (SUCCEEDED(Device->Acquire()))
			{
				HR(Device->GetDeviceState(sizeof(CurrentKey), (LPVOID)CurrentKey));
			}
		}
	}
}

bool Keyboard::KeyUp(byte key) const
{
	return ((CurrentKey[key] & 0x80) == 0);
}

bool Keyboard::KeyDown(byte key) const
{
	return ((CurrentKey[key] & 0x80) != 0);
}

bool Keyboard::KeyHeld(byte key) const
{
	return (KeyDown(key) && KeyWasDown(key));
}

bool Keyboard::KeyWasUp(byte key) const
{
	return ((LastKey[key] & 0x80) == 0);
}

bool Keyboard::KeyWasDown(byte key) const
{
	return ((LastKey[key] & 0x80) == 0);
}