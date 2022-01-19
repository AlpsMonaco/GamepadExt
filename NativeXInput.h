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

		const State* GetState();
		unsigned long errcode;

	protected:
		unsigned long num;
		State state;
	};
}

#endif // !__NATIVE_XINPUT_H


