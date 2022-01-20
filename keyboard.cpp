#include "keyboard.h"
#include <stdio.h>

#ifdef _WIN32

#pragma comment(lib, "User32.lib")
using namespace keyboard;

static OnKeyPressCallback onKeyPressCallback = nullptr;
static DWORD keyboardThreadId = 0;

namespace keyboard
{
	bool PressKeyDetectMethod(KeyCode& keyCode, KeyStatus& keyStatus)
	{
		const char* printFlag = nullptr;
		static char buf[64];
		if (keyCode >= 0x30 && keyCode <= 0x5A)
			printf("%s '%c' 键\r\n", keyStatus == WM_KEYUP ? "释放" : "按下", keyCode);
		else
			printf("%s '<%ld>' 键\r\n", keyStatus == WM_KEYUP ? "释放" : "按下", keyCode);
		return true;
	}
}

OnKeyPressCallback keyboard::PressKeyDetect = PressKeyDetectMethod;

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	KBDLLHOOKSTRUCT* ks = (KBDLLHOOKSTRUCT*)lParam;
	DWORD code = ks->vkCode;
	if (!onKeyPressCallback(ks->vkCode, wParam))return 1;
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

void keyboard::OnKeyPress(OnKeyPressCallback callback)
{
	onKeyPressCallback = callback;
	HINSTANCE hInst = GetModuleHandle(NULL);
	HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, hInst, 0);
	keyboardThreadId = GetCurrentThreadId();
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	UnhookWindowsHookEx(hook);
}

void keyboard::CancelOnKeyPress() { PostThreadMessage(keyboardThreadId, WM_QUIT, 0x00, 0x00); }
#endif