#include "Gamepad.h"
#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib, "setupapi.lib")

using namespace gamepad;

void (*OnError)(const char* errmsg) = [](const char* errmsg) -> void
{ printf("%s\n", errmsg); };

void gamepad::SetErrorHandler(void (*f)(const char* errmsg)) { OnError = f; }

class VigemManagerSingleton
{
public:
    static VigemManagerSingleton* GetInstance();
    PVIGEM_CLIENT* GetClient();

private:
    VigemManagerSingleton();
};

struct VigemManager
{
    VigemManager()
    {
        client = nullptr;
        GetClientPtr = &VigemManager::InitClient;
    }
    ~VigemManager()
    {
        if (client != nullptr)
        {
            vigem_disconnect(client);
            vigem_free(client);
        }
    }
    PVIGEM_CLIENT GetClient()
    {
        return (this->*GetClientPtr)();
    }

private:
    PVIGEM_CLIENT(VigemManager::*GetClientPtr)();
    PVIGEM_CLIENT client;
    PVIGEM_CLIENT InitClient()
    {
        client = vigem_alloc();
        if (client == nullptr)
        {
            OnError("alloc failed");
            return nullptr;
        }
        VIGEM_ERROR retval = vigem_connect(client);
        if (!VIGEM_SUCCESS(retval))
        {
            char errormsg[64];
            sprintf(errormsg, "connect to vigem failed.code: 0x%X", retval);
            OnError(errormsg);
            return nullptr;
        }
        GetClientPtr = &VigemManager::ReuseClient;
        return client;
    }
    inline PVIGEM_CLIENT ReuseClient() { return client; }
} VigemManager;

Gamepad::Gamepad()
{
    this->virtualPad = nullptr;
}

gamepad::Gamepad::~Gamepad() { this->Remove(); }
bool Gamepad::Connect()
{
    if (this->vigemClient == nullptr) {
        OnError("vigem client is nullptr");
        return false;
    }
    return true;
}

void gamepad::Gamepad::Remove()
{
    if (this->vigemClient != nullptr)
    {
        if (this->virtualPad != nullptr)
        {
            vigem_target_remove(this->vigemClient, this->virtualPad);
            vigem_target_free(this->virtualPad);
            this->virtualPad = nullptr;
        }
    }
}

xBox360::xBox360(): Gamepad(){}
xBox360::~xBox360() { }
bool xBox360::Connect()
{
    this->vigemClient = VigemManager.GetClient();
    this->virtualPad = vigem_target_x360_alloc();
    VIGEM_ERROR ret = vigem_target_add(this->vigemClient, this->virtualPad);
    if (!VIGEM_SUCCESS(ret))
    {
        char errormsg[64];

        sprintf(errormsg, "Create virtual pad failed with code: 0x%x", ret);
        OnError(errormsg);
        return false;
    }
    return true;
}

bool xBox360::UpdateState(const State& state)
{
    VIGEM_ERROR ret = vigem_target_x360_update(
        this->vigemClient, this->virtualPad, *(XUSB_REPORT*)&state);
    if (!VIGEM_SUCCESS(ret)) {
        char errormsg[64];
        sprintf(errormsg, "Create virtual pad failed with code: 0x%x", ret);
        OnError(errormsg);
        return false;
    }
    return true;
}
