#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "keyboard.h"
#include "VirtualGamepad.h"

namespace controller
{
    class Controller
    {
    public:
        Controller();
        virtual ~Controller();

        virtual void Start() = 0;
        virtual void Stop() = 0;
    };

    class MapKeyToGamepad : public Controller
    {
    public:
        MapKeyToGamepad();
        ~MapKeyToGamepad();

        void Start();
        void Stop();

        static int threshold;
        static const int defaultThreshold;
        static int rightXThreshold;
        static int rightYThreshold;
        static bool forward;
        static gamepad::XBox360Gamepad* xbox360Gamepad;
        static gamepad::GamepadState state;
        static bool KeyHook(keyboard::KeyCode& keyCode, keyboard::KeyStatus& keyStatus);
    };

    class MapKeyToKey : public Controller
    {
    public:
        MapKeyToKey();
        ~MapKeyToKey();

        void Start();
        void Stop();

        static bool KeyHook(keyboard::KeyCode& keyCode, keyboard::KeyStatus& keyStatus);
        static bool isToggle;
    };

    class CombineKeyAndGamepad : public MapKeyToGamepad
    {
    public:
        CombineKeyAndGamepad();
        ~CombineKeyAndGamepad();

        void Start() override;

        static bool KeyHook(keyboard::KeyCode& keyCode, keyboard::KeyStatus& keyStatus);
        static bool& isToggle;
    };
}

#endif // CONTROLLER_H
