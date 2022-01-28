#ifndef VIGEMMANAGER_H
#define VIGEMMANAGER_H

#include "Types.h"
#include <ViGEm/Client.h>
#include <stdio.h>

namespace gamepad
{
    class VigemManager
    {
    public:
        static VigemManager* GetInstance();
        bool Init();
        const char* Error();
        PVIGEM_CLIENT GetClient();

    private:
        class Deleter
        {
        public:
            Deleter();
            ~Deleter();
        };

        static Deleter deleter;
        static VigemManager* ins;

        PVIGEM_CLIENT client;
        char errorMessage[64];

        VigemManager();
        ~VigemManager();
        void SetError(const char* errorMessage);
    };
}

#endif // VIGEMMANAGER_H
