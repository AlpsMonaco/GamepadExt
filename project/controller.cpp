#include "controller.h"

using namespace controller;

Controller::Controller() { }
Controller::~Controller() { }

MapKeyToGamepad::MapKeyToGamepad() { gamepad::InitGamepadState(MapKeyToGamepad::state); }
MapKeyToGamepad::~MapKeyToGamepad() { }

int MapKeyToGamepad::threshold = 10000;
const int MapKeyToGamepad::defaultThreshold = 12000;
int MapKeyToGamepad::rightXThreshold = defaultThreshold;
int MapKeyToGamepad::rightYThreshold = defaultThreshold;
bool MapKeyToGamepad::forward = false;
gamepad::XBox360Gamepad* MapKeyToGamepad::xbox360Gamepad = nullptr;
gamepad::GamepadState MapKeyToGamepad::state = { 0, 0, 0, { 0, 0 }, { 0, 0 } };

bool MapKeyToGamepad::KeyHook(keyboard::KeyCode& keyCode, keyboard::KeyStatus& keyStatus)
{
    switch (keyCode)
    {
    case VK_NUMPAD4:
    {
        if (keyStatus == WM_KEYDOWN)
            state.rightJoystick.X = -rightXThreshold;
        else
            state.rightJoystick.X = 0;
        xbox360Gamepad->UpdateState(&state);
        return false;
    }
    case VK_NUMPAD6:
    {
        if (keyStatus == WM_KEYDOWN)
            state.rightJoystick.X = rightXThreshold;
        else
            state.rightJoystick.X = 0;
        xbox360Gamepad->UpdateState(&state);
        return false;
    }
    case VK_NUMPAD8:
    {
        if (keyStatus == WM_KEYDOWN)
            state.rightJoystick.Y = rightYThreshold;
        else
            state.rightJoystick.Y = 0;
        xbox360Gamepad->UpdateState(&state);
        return false;
    }
    case VK_NUMPAD2:
    {
        if (keyStatus == WM_KEYDOWN)
            state.rightJoystick.Y = -rightYThreshold;
        else
            state.rightJoystick.Y = 0;
        xbox360Gamepad->UpdateState(&state);
        return false;
    }
    case VK_ADD:
    {
        if (keyStatus == WM_KEYDOWN)
        {
            rightXThreshold += 500;
            rightYThreshold += 500;
            xbox360Gamepad->UpdateState(&state);
        }
        return false;
    }
    case VK_SUBTRACT:
    {
        if (keyStatus == WM_KEYDOWN)
        {
            rightXThreshold -= 500;
            rightYThreshold -= 500;
            xbox360Gamepad->UpdateState(&state);
        }
        return false;
    }
    case VK_MULTIPLY:
    {
        if (keyStatus == WM_KEYDOWN)
        {
            rightYThreshold += 100;
            xbox360Gamepad->UpdateState(&state);
        }
        return false;
    }
    case VK_DIVIDE:
    {
        if (keyStatus == WM_KEYDOWN)
        {
            rightYThreshold -= 100;
            xbox360Gamepad->UpdateState(&state);
        }
        return false;
    }
    case VK_F1:
    {
        if (keyStatus == WM_KEYDOWN)
        {
            forward = !forward;
            if (forward)
            {
                state.leftJoystick.Y = threshold;
                xbox360Gamepad->UpdateState(&state);
            }
            else
            {
                state.leftJoystick.Y = 0;
                xbox360Gamepad->UpdateState(&state);
            }
        }
        return false;
    }
    case VK_W:
    {
        if (keyStatus == WM_KEYDOWN)
        {
            if (forward)
            {
                state.leftJoystick.Y = 0;
                xbox360Gamepad->UpdateState(&state);
            }
            forward = false;
        }
        return true;
    }
    case VK_F2:
    {
        if (keyStatus == WM_KEYDOWN)
        {
            threshold -= 1000;
            if (forward)
                state.leftJoystick.Y = threshold;
            xbox360Gamepad->UpdateState(&state);
        }
        return false;
    }
    case VK_F3:
    {
        if (keyStatus == WM_KEYDOWN)
        {
            threshold += 1000;
            if (forward)
                state.leftJoystick.Y = threshold;
            xbox360Gamepad->UpdateState(&state);
        }
        return false;
    }
    }
    return true;
}

void MapKeyToGamepad::Start()
{
    if (!gamepad::VigemManager::GetInstance()->Init())
        return;
    if (MapKeyToGamepad::xbox360Gamepad == nullptr)
        MapKeyToGamepad::xbox360Gamepad = new gamepad::XBox360Gamepad();
    if (!xbox360Gamepad->Connect())
        return;
    keyboard::SetKeyboardCallback(MapKeyToGamepad::KeyHook);
    keyboard::Hook();
}

void MapKeyToGamepad::Stop()
{
    keyboard::Unhook();
    if (MapKeyToGamepad::xbox360Gamepad != nullptr)
    {
        delete MapKeyToGamepad::xbox360Gamepad;
        MapKeyToGamepad::xbox360Gamepad = nullptr;
    }
}

MapKeyToKey::MapKeyToKey() { isToggle = false; }
MapKeyToKey::~MapKeyToKey() { }

void MapKeyToKey::Start()
{
    keyboard::SetKeyboardCallback(KeyHook);
    keyboard::Hook();
}

void MapKeyToKey::Stop() { keyboard::Unhook(); }

bool MapKeyToKey::isToggle = false;

bool MapKeyToKey::KeyHook(keyboard::KeyCode& keyCode, keyboard::KeyStatus& keyStatus)
{
    switch (keyCode)
    {
    case VK_F1:
        if (keyStatus == WM_KEYUP)
            return false;
        isToggle = !isToggle;
        if (isToggle)
        {
            keybd_event(0, SCAN_CODE_W, KEYEVENTF_SCANCODE, 0);
            keybd_event(0, SCAN_CODE_LCTRL, KEYEVENTF_SCANCODE, 0);
        }
        else
        {
            keybd_event(0, SCAN_CODE_W, KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP, 0);
            keybd_event(0, SCAN_CODE_LCTRL, KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP, 0);
        }
        return false;
    case VK_W:
        if (keyStatus == WM_KEYUP)
        {
            isToggle = false;
        }
        else
        {
            if (isToggle)
                keybd_event(0, SCAN_CODE_LCTRL, KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP, 0);
        }
        return true;
    default:
        break;
    }
    return true;
}

CombineKeyAndGamepad::CombineKeyAndGamepad()
    : MapKeyToGamepad()
{
    isToggle = false;
}
void CombineKeyAndGamepad::Start()
{
    if (!gamepad::VigemManager::GetInstance()->Init())
        return;
    if (MapKeyToGamepad::xbox360Gamepad == nullptr)
        MapKeyToGamepad::xbox360Gamepad = new gamepad::XBox360Gamepad();
    if (!xbox360Gamepad->Connect())
        return;
    keyboard::SetKeyboardCallback(KeyHook);
    keyboard::Hook();
}

bool& CombineKeyAndGamepad::isToggle = MapKeyToKey::isToggle;

bool CombineKeyAndGamepad::KeyHook(keyboard::KeyCode& keyCode, keyboard::KeyStatus& keyStatus)
{
    switch (keyCode)
    {
    case VK_F1:
        if (keyStatus == WM_KEYUP)
            return false;
        isToggle = !isToggle;
        if (isToggle)
        {
            keybd_event(0, SCAN_CODE_W, KEYEVENTF_SCANCODE, 0);
            keybd_event(0, SCAN_CODE_LCTRL, KEYEVENTF_SCANCODE, 0);
        }
        else
        {
            keybd_event(0, SCAN_CODE_W, KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP, 0);
            keybd_event(0, SCAN_CODE_LCTRL, KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP, 0);
        }
        return false;
    case VK_W:
        if (keyStatus == WM_KEYUP)
        {
            isToggle = false;
        }
        else
        {
            if (isToggle)
                keybd_event(0, SCAN_CODE_LCTRL, KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP, 0);
            if (forward)
            {
                state.leftJoystick.Y = 0;
                xbox360Gamepad->UpdateState(&state);
            }
            forward = false;
        }
        return true;
    case VK_NUMPAD4:
    {
        if (keyStatus == WM_KEYDOWN)
            state.rightJoystick.X = -rightXThreshold;
        else
            state.rightJoystick.X = 0;
        xbox360Gamepad->UpdateState(&state);
        return false;
    }
    case VK_NUMPAD6:
    {
        if (keyStatus == WM_KEYDOWN)
            state.rightJoystick.X = rightXThreshold;
        else
            state.rightJoystick.X = 0;
        xbox360Gamepad->UpdateState(&state);
        return false;
    }
    case VK_NUMPAD8:
    {
        if (keyStatus == WM_KEYDOWN)
            state.rightJoystick.Y = rightYThreshold;
        else
            state.rightJoystick.Y = 0;
        xbox360Gamepad->UpdateState(&state);
        return false;
    }
    case VK_NUMPAD2:
    {
        if (keyStatus == WM_KEYDOWN)
            state.rightJoystick.Y = -rightYThreshold;
        else
            state.rightJoystick.Y = 0;
        xbox360Gamepad->UpdateState(&state);
        return false;
    }
    case VK_ADD:
    {
        if (keyStatus == WM_KEYDOWN)
        {
            rightXThreshold += 500;
            rightYThreshold += 500;
            xbox360Gamepad->UpdateState(&state);
        }
        return false;
    }
    case VK_SUBTRACT:
    {
        if (keyStatus == WM_KEYDOWN)
        {
            rightXThreshold -= 500;
            rightYThreshold -= 500;
            xbox360Gamepad->UpdateState(&state);
        }
        return false;
    }
    case VK_MULTIPLY:
    {
        if (keyStatus == WM_KEYDOWN)
        {
            rightYThreshold += 100;
            xbox360Gamepad->UpdateState(&state);
        }
        return false;
    }
    case VK_DIVIDE:
    {
        if (keyStatus == WM_KEYDOWN)
        {
            rightYThreshold -= 100;
            xbox360Gamepad->UpdateState(&state);
        }
        return false;
    }
    case VK_F5:
    {
        if (keyStatus == WM_KEYDOWN)
        {
            forward = !forward;
            if (forward)
            {
                state.leftJoystick.Y = threshold;
                xbox360Gamepad->UpdateState(&state);
            }
            else
            {
                state.leftJoystick.Y = 0;
                xbox360Gamepad->UpdateState(&state);
            }
        }
        return false;
    }
    case VK_F6:
    {
        if (keyStatus == WM_KEYDOWN)
        {
            threshold -= 1000;
            if (forward)
                state.leftJoystick.Y = threshold;
            xbox360Gamepad->UpdateState(&state);
        }
        return false;
    }
    case VK_F7:
    {
        if (keyStatus == WM_KEYDOWN)
        {
            threshold += 1000;
            if (forward)
                state.leftJoystick.Y = threshold;
            xbox360Gamepad->UpdateState(&state);
        }
        return false;
    }
    default:
        break;
    }
    return true;
}

CombineKeyAndGamepad::~CombineKeyAndGamepad() { }
