#include "NativeXInput.h"

using namespace gamepad;

gamepad::NativeXInput::NativeXInput()
{
	this->num = 0;
	this->state.gamepadState.button = 0;
	this->state.gamepadState.leftJoystick = { 0,0 };
	this->state.gamepadState.rightJoystick = { 0,0 };
	this->state.gamepadState.leftTrigger = 0;
	this->state.gamepadState.rightTrigger = 0;
	this->state.packetNumber = 0;
	this->errcode = 0;
}

gamepad::NativeXInput::NativeXInput(unsigned long num)
{
	this->num = num;
	this->state.gamepadState.button = 0;
	this->state.gamepadState.leftJoystick = { 0,0 };
	this->state.gamepadState.rightJoystick = { 0,0 };
	this->state.gamepadState.leftTrigger = 0;
	this->state.gamepadState.rightTrigger = 0;
	this->state.packetNumber = 0;
	this->errcode = 0;
}

gamepad::NativeXInput::~NativeXInput() {}

const XInputState* gamepad::NativeXInput::GetState()
{
	this->errcode = XInputGetState(this->num, (XINPUT_STATE*)&this->state);
	return this->errcode == ERROR_SUCCESS ? &this->state : nullptr;
}
