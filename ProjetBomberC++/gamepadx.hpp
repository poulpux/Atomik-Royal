#pragma once

#include "SFML/Graphics.hpp"

namespace gp {

    class Gamepad {

    public:

        // Typedefs
        typedef unsigned int    t_joyNum;
        typedef unsigned short  t_buttonNum;

        // Enums
        enum {
            Count = 4       // Player 0-3
        };

        enum {
            DPAD_UP = 0x0001,
            DPAD_DOWN = 0x0002,
            DPAD_LEFT = 0x0004,
            DPAD_RIGHT = 0x0008,
            START = 0x0010,
            BACK = 0x0020,
            LEFT_THUMB = 0x0040,
            RIGHT_THUMB = 0x0080,
            LB = 0x0100,
            RB = 0x0200,
            A = 0x1000,
            B = 0x2000,
            X = 0x4000,
            Y = 0x8000,
        };

        // Méthode static pour être utilisé sans instancier d'objet
        static bool isConnected(t_joyNum joyNum);
        static unsigned int getButtonCount(t_joyNum joyNum) { return 14; }
        static bool isButtonPressed(t_joyNum joyNum, t_buttonNum buttonNum);
        static bool voiceSupported(t_joyNum joyNum);
        static bool isAnyXBox360ControllerConnected();
        static void getTriggers(t_joyNum joyNum, float& left, float& right);
        static void getSticksPosition(t_joyNum joyNum, sf::Vector2f& left, sf::Vector2f& right);
        static void setVibration(t_joyNum, float leftMotor = 0.0f, float rightMotor = 0.0f);

    };

}

