#pragma once

#ifndef __GAMEPAD_TYPES
#define __GAMEPAD_TYPES

#include <Windows.h>
#include <Xinput.h>

namespace gamepad
{
    using Trigger = unsigned char;
    using Button = unsigned short;
    using PacketNumber = unsigned long;
    using Joystick = struct
    {
        SHORT X;
        SHORT Y;
    };

    struct State
    {
        Button button;
        Trigger leftTrigger;
        Trigger rightTrigger;
        Joystick leftJoystick;
        Joystick rightJoystick;
    };

    struct XInputState
    {
        PacketNumber packetNumber;
        State gamepadState;
    };

    enum GamepadKey
    {
        DPAD_UP = 0x0001,
        DPAD_DOWN = 0x0002,
        DPAD_LEFT = 0x0004,
        DPAD_RIGHT = 0x0008,
        START = 0x0010,
        BACK = 0x0020,
        LEFT_THUMB = 0x0040,
        RIGHT_THUMB = 0x0080,
        LEFT_SHOULDER = 0x0100,
        RIGHT_SHOULDER = 0x0200,
        A = 0x1000,
        B = 0x2000,
        X = 0x4000,
        Y = 0x8000,
    };

} // namespace gamepad

#endif // !__GAMEPAD_TYPES
