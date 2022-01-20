#include <iostream>
#include <string>

#include "NativeXInput.h"
#include "gamepad.h"
#include "keyboard.h"
#include "thread"

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
bool forward = false;
bool GameForward(keyboard::KeyCode& keyCode, keyboard::KeyStatus& keyStatus)
{
	if (keyCode == VK_F2 && keyStatus == WM_KEYDOWN)
	{
		std::cout << 1 << std::endl;
		state.button |= gamepad::GamepadKey::A;
		pad.UpdateState(state);
		return false;
	}
	if (keyCode == VK_F2 && keyStatus == WM_KEYUP)
	{
		std::cout << 2 << std::endl;
		state.button &= ~gamepad::GamepadKey::A;
		pad.UpdateState(state);
		return false;
	}
	if (keyCode != VK_F1 || keyStatus != WM_KEYDOWN) return true;
	forward = !forward;
	if (forward)
		state.leftJoystick.Y = threshold;
	else
		state.leftJoystick.Y = 0;
	std::cout << 3 << std::endl;
	pad.UpdateState(state);
	return false;
}



int main(int argc, char** argv)
{
	if (argc > 1) threshold = std::atoi(argv[1]);
	if (!pad.Connect())
		return 1;
	keyboard::OnKeyPress(GameForward);
	for (;;)
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	return 0;
}