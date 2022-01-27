#ifndef TYPES_H
#define TYPES_H

#include <Windows.h>
#include <Xinput.h>
#pragma comment(lib, "setupapi.lib")

using Trigger = unsigned char;
using Button = unsigned short;
using PacketNumber = unsigned long;
using Joystick = struct
{
    SHORT X;
    SHORT Y;
};

struct GamepadState
{
    Button button;
    Trigger leftTrigger;
    Trigger rightTrigger;
    Joystick leftJoystick;
    Joystick rightJoystick;
};

union State
{
    XINPUT_STATE xinput;
    struct
    {
        PacketNumber packetNumber;
        GamepadState gamepadState;
    } gamepadInput;
};

#endif // TYPES_H
