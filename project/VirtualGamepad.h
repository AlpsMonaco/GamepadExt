#ifndef VIRTUALGAMEPAD_H
#define VIRTUALGAMEPAD_H

#include "VigemManager.h"

class VirtualGamepad
{
public:
    VirtualGamepad();
    virtual ~VirtualGamepad();

    virtual PVIGEM_TARGET GetTarget() = 0;
    virtual bool UpdateState(const GamepadState* state) = 0;

    bool Connect();
    bool Disconnect();
    void SetErrorMessage(const char* errorMessage);
    const char* Error();

protected:
    PVIGEM_CLIENT client;
    PVIGEM_TARGET target;
    char errorMessage[64];
};

class XBox360Gamepad : public VirtualGamepad
{
public:
    XBox360Gamepad();
    ~XBox360Gamepad();

    PVIGEM_TARGET GetTarget();
    bool UpdateState(const GamepadState* state);

protected:
};

#endif // VIRTUALGAMEPAD_H
