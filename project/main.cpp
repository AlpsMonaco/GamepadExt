#include "mainwindow.h"
#include <QApplication>
#include "VirtualGamepad.h"
#include "keyboard.h"

XBox360Gamepad* xbox360Gamepad = nullptr;
GamepadState state;

int threshold = 10000;
const int defaultThreshold = 12000;
int rightXThreshold = defaultThreshold;
int rightYThreshold = defaultThreshold;
bool forward = false;

bool KeyToGamepad(keyboard::KeyCode& keyCode, keyboard::KeyStatus& keyStatus)
{
    if (keyCode == VK_NUMPAD4)
    {
        if (keyStatus == WM_KEYDOWN)
            state.rightJoystick.X = -rightXThreshold;
        else
            state.rightJoystick.X = 0;
        xbox360Gamepad->UpdateState(&state);
        return false;
    }
    if (keyCode == VK_NUMPAD6)
    {
        if (keyStatus == WM_KEYDOWN)
            state.rightJoystick.X = rightXThreshold;
        else
            state.rightJoystick.X = 0;
        xbox360Gamepad->UpdateState(&state);
        return false;
    }
    if (keyCode == VK_NUMPAD8)
    {
        if (keyStatus == WM_KEYDOWN)
            state.rightJoystick.Y = rightYThreshold;
        else
            state.rightJoystick.Y = 0;
        xbox360Gamepad->UpdateState(&state);
        return false;
    }
    if (keyCode == VK_NUMPAD2)
    {
        if (keyStatus == WM_KEYDOWN)
            state.rightJoystick.Y = -rightYThreshold;
        else
            state.rightJoystick.Y = 0;
        xbox360Gamepad->UpdateState(&state);
        return false;
    }
    if (keyCode == VK_ADD)
    {
        if (keyStatus == WM_KEYDOWN)
        {
            rightXThreshold += 500;
            rightYThreshold += 500;
            xbox360Gamepad->UpdateState(&state);
        }
        return false;
    }
    if (keyCode == VK_SUBTRACT)
    {
        if (keyStatus == WM_KEYDOWN)
        {
            rightXThreshold -= 500;
            rightYThreshold -= 500;
            xbox360Gamepad->UpdateState(&state);
        }
        return false;
    }
    if (keyCode == VK_MULTIPLY)
    {
        if (keyStatus == WM_KEYDOWN)
        {
            rightYThreshold += 100;
            xbox360Gamepad->UpdateState(&state);
        }
        return false;
    }
    if (keyCode == VK_DIVIDE)
    {
        if (keyStatus == WM_KEYDOWN)
        {
            rightYThreshold -= 100;
            xbox360Gamepad->UpdateState(&state);
        }
        return false;
    }
    if (keyCode == VK_F1)
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
    if (keyCode == VK_W)
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
    if (keyCode == VK_F2)
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
    if (keyCode == VK_F3)
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
    return true;
}

bool Start()
{
    if (!VigemManager::GetInstance()->Init())
    {
        qDebug() << VigemManager::GetInstance()->Error();
        return false;
    }
    xbox360Gamepad = new XBox360Gamepad();
    if (!xbox360Gamepad->Connect())
    {
        qDebug() << xbox360Gamepad->Error();
        delete xbox360Gamepad;
        return false;
    }
    keyboard::SetKeyboardCallback(KeyToGamepad);
    keyboard::Hook();
    return true;
}

struct Init
{
    Init() { }
    ~Init()
    {
        keyboard::Unhook();
        if (xbox360Gamepad != nullptr)
        {
            delete xbox360Gamepad;
        }
    }
} init;

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Start();
    return a.exec();
}
