#include "gamepad.h"
#include "NativeXInput.h"
#include "thread"
#include <iostream>
#include <string>

int main(int argc, char** argv) 
{
	gamepad::NativeXInput xinput(0);
	gamepad::Gamepad *gamepad = new gamepad::xBox360(); 
	if (!gamepad->Connect()) { delete gamepad; return 1;delete gamepad; }
	gamepad::State state;
	state.leftJoystick.X = 10;
	if (gamepad->UpdateState(state)) 
	{
		const gamepad::State* xinputState = xinput.GetState();
		std::cout << std::to_string(state.leftJoystick.X) << std::endl;
	}
	delete gamepad;
	return 0;
}