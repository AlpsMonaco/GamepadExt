#include "VigemManager.h"

using namespace gamepad;

VigemManager* VigemManager::ins = nullptr;
VigemManager::Deleter VigemManager::deleter = VigemManager::Deleter();

VigemManager::Deleter::Deleter() { }
VigemManager::Deleter::~Deleter()
{
    if (VigemManager::ins != nullptr)
    {
        delete VigemManager::ins;
    }
}

VigemManager* VigemManager::GetInstance()
{
    if (VigemManager::ins == nullptr)
        VigemManager::ins = new VigemManager();
    return VigemManager::ins;
}

VigemManager::VigemManager()
{
    for (int i = 0; i < 64; i++)
        this->errorMessage[i] = 0;
    this->client = nullptr;
}

VigemManager::~VigemManager()
{
    if (client != nullptr)
    {
        vigem_disconnect(client);
        vigem_free(client);
    }
}

bool VigemManager::Init()
{
    if (this->client == nullptr)
    {
        this->client = vigem_alloc();
        if (this->client == nullptr)
        {
            SetError("vigem_alloc failed.");
            return false;
        }
        VIGEM_ERROR retval = vigem_connect(this->client);
        if (!VIGEM_SUCCESS(retval))
        {
            sprintf(this->errorMessage, "connect to vigem failed.code: 0x%X", retval);
            return false;
        }
    }
    return true;
}

void VigemManager::SetError(const char* errorMessage)
{
    char* dst = this->errorMessage;
    do
    {
    } while ((*(dst++) = *(errorMessage++)) != '\0');
}

PVIGEM_CLIENT VigemManager::GetClient() { return this->client; }
const char* VigemManager::Error() { return this->errorMessage; }
