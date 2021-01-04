#include "stdafx.h"
#include "InstallHooks.h"
#include "Hooking.h"
#include <dinput.h>
#include <iostream>

extern HMODULE DllHandle;

LPDIRECTINPUT8 pDinput8A;

static GUID controllerGuid = GUID_NULL;
const int controllerGuidsLength = 32;
static GUID controllerGuids[controllerGuidsLength];
static int controllerIndex = 0;

const HRESULT blockReturnValue = DIERR_INVALIDPARAM;

static BOOL CALLBACK DIEnumDevicesCallback(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef)
{
	auto di = *lpddi;
	const auto i = static_cast<int*>(pvRef);
	
	/* https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf page 26:
		4 : Joystick
		5 : Game Pad */
	if (di.wUsage == 4 || di.wUsage == 5)
	{
		controllerGuids[*i] = di.guidInstance;

		*i += 1;
		if (*i == controllerIndex)//controllerIndex starts at 1
		{
			controllerGuid = di.guidInstance;
			std::cout << "Selected controller, instanceName=" << di.tszInstanceName << ", productName=" << di.tszProductName << ", usage=" << di.wUsage << 
				", usagePage=" << di.wUsagePage << ", *i=" << *i << "\n";
		}
	}	

	return DIENUM_CONTINUE;
}

void GetDinput8CreateDevicePtr(void** ptrA, void** ptrW)
{
	auto vPtrDinput8A = *(PtrSize**)(pDinput8A);
	*ptrA = (void*)(vPtrDinput8A[3]);

	void* pDinput8W;
	if (DI_OK == DirectInput8Create(DllHandle, DIRECTINPUT_VERSION, IID_IDirectInput8W, reinterpret_cast<void**>(&pDinput8W), nullptr))
	{
		PtrSize* vPtrDinput8W = *(PtrSize**)(pDinput8W);
		*ptrW = (void*)(vPtrDinput8W[3]);
	}
}

void GetDinput7CreateDevicePtr(void** ptrA, void** ptrW)
{
	LoadLibrary("dinput.dll");
	const auto directInputCreateEx = GetProcAddress(GetModuleHandle("dinput.dll"), "DirectInputCreateEx");
	typedef HRESULT(__stdcall * FuncDirectInputCreateEx)(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID *ppvOut, LPUNKNOWN punkOuter);
	static auto DirectInputCreateEx = FuncDirectInputCreateEx(directInputCreateEx);

	void* pDinput7A;
	if (DI_OK == DirectInputCreateEx(DllHandle, 0x0700, IID_IDirectInput7A, &pDinput7A, nullptr))
	{
		PtrSize* vPtrDinput7A = *(PtrSize**)(pDinput7A);
		*ptrA = (void*)(vPtrDinput7A[3]);
	}

	void* pDinput7W;
	if (DI_OK == DirectInputCreateEx(DllHandle, 0x0700, IID_IDirectInput7W, &pDinput7W, nullptr))
	{
		PtrSize* vPtrDinput7W = *(PtrSize**)(pDinput7W);
		*ptrW = (void*)(vPtrDinput7W[3]);
	}
}

HRESULT __stdcall Dinput8_CreateDeviceA_Hook(IDirectInput8A* pDin, REFGUID rguid, LPDIRECTINPUTDEVICE8A* lplpDirectInputDevice, LPUNKNOWN pUnkOuter)
{
	std::cout << "Dinput8 CreateDeviceHookA called\n";

	//if (controllerIndex == 0)
	//	return blockReturnValue;

	for (auto i : controllerGuids)
	{
		if (i == rguid)
		{
			//They are getting input from a controller
			return pDin->CreateDevice(controllerGuid, lplpDirectInputDevice, pUnkOuter);
		}
	}

	//They are probably getting input from a mouse/keyboard
	return pDin->CreateDevice(rguid, lplpDirectInputDevice, pUnkOuter);
}

HRESULT __stdcall Dinput8_CreateDeviceW_Hook(IDirectInput8W* pDin, REFGUID rguid, LPDIRECTINPUTDEVICE8W* lplpDirectInputDevice, LPUNKNOWN pUnkOuter)
{
	std::cout << "Dinput8 CreateDeviceHookW called\n";

	//if (controllerIndex == 0)
	//	return blockReturnValue;

	for (auto i : controllerGuids)
	{
		if (i == rguid)
		{
			//They are getting input from a controller
			return pDin->CreateDevice(controllerGuid, lplpDirectInputDevice, pUnkOuter);
		}
	}

	//They are probably getting input from a mouse/keyboard
	return pDin->CreateDevice(rguid, lplpDirectInputDevice, pUnkOuter);
}

HRESULT __stdcall Dinput7_CreateDeviceA_Hook(IDirectInput7A* pDin, REFGUID rguid, LPDIRECTINPUTDEVICEA* lplpDirectInputDevice, LPUNKNOWN pUnkOuter)
{
	std::cout << "Dinput7 CreateDeviceHookA called\n";

	//if (controllerIndex == 0)
	//	return blockReturnValue;

	for (auto i : controllerGuids)
	{
		if (i == rguid)
		{
			//They are getting input from a controller
			return pDin->CreateDevice(controllerGuid, lplpDirectInputDevice, pUnkOuter);
		}
	}

	//They are probably getting input from a mouse/keyboard
	return pDin->CreateDevice(rguid, lplpDirectInputDevice, pUnkOuter);
}

HRESULT __stdcall Dinput7_CreateDeviceW_Hook(IDirectInput7W* pDin, REFGUID rguid, LPDIRECTINPUTDEVICEW* lplpDirectInputDevice, LPUNKNOWN pUnkOuter)
{
	std::cout << "Dinput7 CreateDeviceHookW called\n";

	//if (controllerIndex == 0)
	//	return blockReturnValue;

	for (auto i : controllerGuids)
	{
		if (i == rguid)
		{
			//They are getting input from a controller
			return pDin->CreateDevice(controllerGuid, lplpDirectInputDevice, pUnkOuter);
		}
	}

	//They are probably getting input from a mouse/keyboard
	return pDin->CreateDevice(rguid, lplpDirectInputDevice, pUnkOuter);
}

void installDirectInputHooks(int _controllerIndex)
{
	controllerIndex = _controllerIndex;

	if (DI_OK != DirectInput8Create(DllHandle, DIRECTINPUT_VERSION, IID_IDirectInput8A, reinterpret_cast<void**>(&pDinput8A), nullptr))
	{
		std::cerr << "Error creating dinput8 interface" << std::endl;
		MessageBox(nullptr, "Error creating dinput8 interface", "DirectInput8 error", MB_OK);
		return;
	}

	if (controllerIndex != 0)
	{
		int i = 0;
		pDinput8A->EnumDevices(DI8DEVCLASS_ALL, DIEnumDevicesCallback, &i, DIEDFL_ALLDEVICES);

		if (controllerGuid == GUID_NULL)
		{
			std::cerr << "Not enough controllers" << std::endl;
			MessageBox(nullptr, "Not enough controllers", "DirectInput8 error", MB_OK);
			return;
		}
	}

	void* pDinput8CreateDeviceA;
	void* pDinput8CreateDeviceW;
	GetDinput8CreateDevicePtr(&pDinput8CreateDeviceA, &pDinput8CreateDeviceW);

	installHook(pDinput8CreateDeviceA, Dinput8_CreateDeviceA_Hook, "Dinput8 CreateDeviceA");
	installHook(pDinput8CreateDeviceW, Dinput8_CreateDeviceW_Hook, "Dinput8 CreateDeviceW");

	void* pDinput7CreateDeviceA;
	void* pDinput7CreateDeviceW;
	GetDinput7CreateDevicePtr(&pDinput7CreateDeviceA, &pDinput7CreateDeviceW);

	installHook(pDinput7CreateDeviceA, Dinput7_CreateDeviceA_Hook, "Dinput7 CreateDeviceA");
	installHook(pDinput7CreateDeviceW, Dinput7_CreateDeviceW_Hook, "Dinput7 CreateDeviceW");
}
