#include "VirtualGamepad.h"

using namespace gamepad;

void gamepad::InitGamepadState(GamepadState& state)
{
    state.button = 0;
    state.leftTrigger = 0;
    state.rightTrigger = 0;
    state.leftJoystick.X = 0;
    state.leftJoystick.Y = 0;
    state.rightJoystick.X = 0;
    state.rightJoystick.Y = 0;
}

const char* VirtualGamepad::Error() { return this->errorMessage; }

XBox360Gamepad::~XBox360Gamepad() { }
PVIGEM_TARGET XBox360Gamepad::GetTarget() { return vigem_target_x360_alloc(); }

VirtualGamepad::~VirtualGamepad()
{
    this->Disconnect();
    this->client = nullptr;
}

VirtualGamepad::VirtualGamepad()
{
    this->client = VigemManager::GetInstance()->GetClient();
    this->target = nullptr;
}

void VirtualGamepad::SetErrorMessage(const char* errorMessage)
{
    char* dst = this->errorMessage;
    do
    {
    } while ((*(dst++) = *(errorMessage++)) != 0);
}

bool VirtualGamepad::Connect()
{
    if (this->client == nullptr)
    {
        this->SetErrorMessage("client is nullptr");
        return false;
    }
    this->target = this->GetTarget();
    if (this->target == nullptr)
    {
        this->SetErrorMessage("get vigem target failed");
        return false;
    }
    VIGEM_ERROR ret = vigem_target_add(this->client, this->target);
    if (!VIGEM_SUCCESS(ret))
    {
        sprintf(this->errorMessage, "Create virtual gamepad failed with code: 0x%x", ret);
        return false;
    }
    return true;
}

bool VirtualGamepad::Disconnect()
{
    if (this->client != nullptr)
    {
        if (this->target != nullptr)
        {
            vigem_target_remove(this->client, this->target);
            vigem_target_free(this->target);
            this->target = nullptr;
        }
    }
    return true;
}

XBox360Gamepad::XBox360Gamepad()
    : VirtualGamepad()
{
}

bool XBox360Gamepad::UpdateState(const GamepadState* state)
{
    VIGEM_ERROR ret = vigem_target_x360_update(this->client, this->target, *(XUSB_REPORT*)state);
    if (!VIGEM_SUCCESS(ret))
    {
        sprintf(this->errorMessage, "update x360 state failed: 0x%x", ret);
        return false;
    }
    return true;
}
