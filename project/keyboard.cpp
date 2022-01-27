#include "keyboard.h"

using namespace keyboard;

HHOOK keyboardHook = NULL;
KeyboardCallback keyboardCallback = nullptr;

void keyboard::SetKeyboardCallback(KeyboardCallback callback) { keyboardCallback = callback; }

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    KBDLLHOOKSTRUCT* ks = (KBDLLHOOKSTRUCT*)lParam;
    if (keyboardCallback(ks->vkCode, wParam))
        return CallNextHookEx(NULL, nCode, wParam, lParam);
    return 1;
}

bool keyboard::Hook()
{
    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
    return keyboardHook != NULL;
}

void keyboard::Unhook()
{
    if (keyboardHook != NULL)
        UnhookWindowsHookEx(keyboardHook);
}
