#pragma once
#ifndef __NATIVE_XINPUT_H
#define __NATIVE_XINPUT_H

#include "types.h"

namespace gamepad
{
	class NativeXInput
	{
	public:
		NativeXInput();
		NativeXInput(unsigned long num);
		~NativeXInput();

		const XInputState* GetState();
		unsigned long errcode;

	protected:
		unsigned long num;
		XInputState state;
	};
}

#endif // !__NATIVE_XINPUT_H


