#include <iostream>
#include <string>

#include "NativeXInput.h"
#include "gamepad.h"
#include "keyboard.h"
#include "thread"
#include "atomic"

gamepad::xBox360 pad;
gamepad::State state;

void ReleaseKey(keyboard::KeyCode& keyCode)
{
	switch (keyCode)
	{
	case VK_F1:
		state.leftJoystick.X = 0;
		break;
	case VK_F2:
		state.leftJoystick.Y = 0;
		break;
	case VK_F3:
		state.leftJoystick.X = 0;
		break;
	case VK_F4:
		state.leftJoystick.Y = 0;
		break;
	case VK_W:
		state.button &= ~gamepad::GamepadKey::DPAD_UP;
		break;
	case VK_S:
		state.button &= ~gamepad::GamepadKey::DPAD_DOWN;
		break;
	case VK_A:
		state.button &= ~gamepad::GamepadKey::DPAD_LEFT;
		break;
	case VK_D:
		state.button &= ~gamepad::GamepadKey::DPAD_RIGHT;
		break;
	case VK_J:
		state.button &= ~gamepad::GamepadKey::A;
		break;
	case VK_K:
		state.button &= ~gamepad::GamepadKey::B;
		break;
	default:
		break;
	}
}

void PressKey(keyboard::KeyCode& keyCode)
{
	switch (keyCode)
	{
	case VK_F1:
		state.leftJoystick.X = 10000;
		break;
	case VK_F2:
		state.leftJoystick.Y = 10000;
		break;
	case VK_F3:
		state.leftJoystick.X = -10000;
		break;
	case VK_F4:
		state.leftJoystick.Y = -10000;
		break;
	case VK_W:
		state.button |= gamepad::GamepadKey::DPAD_UP;
		break;
	case VK_S:
		state.button |= gamepad::GamepadKey::DPAD_DOWN;
		break;
	case VK_A:
		state.button |= gamepad::GamepadKey::DPAD_LEFT;
		break;
	case VK_D:
		state.button |= gamepad::GamepadKey::DPAD_RIGHT;
		break;
	case VK_J:
		state.button |= gamepad::GamepadKey::A;
		break;
	case VK_K:
		state.button |= gamepad::GamepadKey::B;
		break;
	default:
		break;
	}
}

bool Control(keyboard::KeyCode& keyCode, keyboard::KeyStatus& keyStatus)
{
	if (keyStatus == WM_KEYUP)
		ReleaseKey(keyCode);
	else
		PressKey(keyCode);
	pad.UpdateState(state);
	std::cout << state.button << std::endl;
	return false;
}
int threshold = 10000;
const int defaultThreshold = 12000;

int rightXThreshold = defaultThreshold;
int rightYThreshold = defaultThreshold;
bool forward = false;

bool GameForward(keyboard::KeyCode& keyCode, keyboard::KeyStatus& keyStatus)
{
	if (keyCode == VK_NUMPAD4)
	{
		if (keyStatus == WM_KEYDOWN)
			state.rightJoystick.X = -rightXThreshold;
		else
			state.rightJoystick.X = 0;
		pad.UpdateState(state);
		return false;
	}
	if (keyCode == VK_NUMPAD6)
	{
		if (keyStatus == WM_KEYDOWN)
			state.rightJoystick.X = rightXThreshold;
		else
			state.rightJoystick.X = 0;
		pad.UpdateState(state);
		return false;
	}
	if (keyCode == VK_NUMPAD8)
	{
		if (keyStatus == WM_KEYDOWN)
			state.rightJoystick.Y = rightYThreshold;
		else
			state.rightJoystick.Y = 0;
		pad.UpdateState(state);
		return false;
	}
	if (keyCode == VK_NUMPAD2)
	{
		if (keyStatus == WM_KEYDOWN)
			state.rightJoystick.Y = -rightYThreshold;
		else
			state.rightJoystick.Y = 0;
		pad.UpdateState(state);
		return false;
	}
	if (keyCode == VK_ADD)
	{
		if (keyStatus == WM_KEYDOWN)
		{
			rightXThreshold += 500;
			rightYThreshold += 500;
			pad.UpdateState(state);
		}
		return false;
	}
	if (keyCode == VK_SUBTRACT)
	{
		if (keyStatus == WM_KEYDOWN)
		{
			rightXThreshold -= 500;
			rightYThreshold -= 500;
			std::cout << rightXThreshold << std::endl;
			pad.UpdateState(state);
		}
		return false;
	}
	if (keyCode == VK_MULTIPLY)
	{
		if (keyStatus == WM_KEYDOWN)
		{
			rightYThreshold += 100;
			std::cout << rightXThreshold << std::endl;
			pad.UpdateState(state);
		}
		return false;
	}
	if (keyCode == VK_DIVIDE)
	{
		if (keyStatus == WM_KEYDOWN)
		{
			rightYThreshold -= 100;
			std::cout << rightXThreshold << std::endl;
			pad.UpdateState(state);
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
				pad.UpdateState(state);
			}
			else
			{
				state.leftJoystick.Y = 0;
				pad.UpdateState(state);
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
				pad.UpdateState(state);
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
			pad.UpdateState(state);
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
			pad.UpdateState(state);
		}
		return false;
	}
	return true;
}



int main(int argc, char** argv)
{
	if (argc > 1) threshold = std::atoi(argv[1]);
	if (!pad.Connect())
		return 1;
	keyboard::OnKeyPress(GameForward);
	for (;;)
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	return 0;
}