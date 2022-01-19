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
		PacketNumber packetNumber;
		Button button;
		Trigger leftTrigger;
		Trigger  rightTrigger;
		Joystick leftJoystick;
		Joystick rightJoystick;
	};
}

#endif // !__GAMEPAD_TYPES
