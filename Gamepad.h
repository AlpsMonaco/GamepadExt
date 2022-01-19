#pragma once
#ifndef __GAMEPAD_H
#define __GAMEPAD_H

#include "types.h"
#include <ViGEm/Client.h>

namespace gamepad
{
	// If internal error occurs,error message will be sent to ErrorHandleCallback;
	// Customize ErrorHandle callback here.
	// Default Will be output to stdout.
	void SetErrorHandler(void(*f)(const char* errmsg));

	enum GamepadType
	{
		Gamepad_Xbox360,
		Gamepad_PS4,
	};

	class Gamepad
	{
	public:
		Gamepad();
		virtual ~Gamepad();

		virtual bool Connect() = 0;
		virtual bool UpdateState(const State& state) = 0;
		void Remove();

	protected:
		PVIGEM_CLIENT vigemClient;
		PVIGEM_TARGET virtualPad;
	};


	class xBox360 :public Gamepad
	{
	public:
		xBox360();
		~xBox360();

		bool Connect();
		bool UpdateState(const State& state);
	};
}


#endif // __GAMEPAD_H