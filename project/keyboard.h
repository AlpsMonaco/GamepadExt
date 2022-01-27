#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "keyboard_define.h"

#ifdef _WIN32
#include <Windows.h>
#pragma comment(lib, "User32.Lib")
#else
#endif

namespace keyboard
{
    using KeyCode = DWORD;
    using KeyStatus = WPARAM;
    using KeyboardCallback = bool (*)(KeyCode& keyCode, KeyStatus& keystatus);

    void SetKeyboardCallback(KeyboardCallback callback);
    bool Hook();
    void Unhook();
}

#endif // KEYBOARD_H
