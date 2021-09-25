#pragma once

#include "../Hukan.hpp"

namespace hk {
    enum class Color : Int_t {
        Reset = Bit(0),
        Red = Bit(1),
        DarkRed = Bit(2),
        Green = Bit(3),
        DarkGreen = Bit(4),
        Yellow = Bit(5),
        DarkYellow = Bit(6),
        Blue = Bit(7),
        DarkBlue = Bit(8),
        Magenta = Bit(9),
        DarkMagenta = Bit(10),
        Cyan = Bit(11),
        DarkCyan = Bit(12),
        Gray = Bit(13),
        White = Bit(14)
    };

    extern void HK_API AsColor(Color color);
    extern void HK_API AvailableColors();
};