#pragma once

#include "../Hukan.hpp"

namespace hk {
    enum class Color : Int_t {
        Reset = Bit(0),
        Black = Bit(1),
        Red = Bit(2),
        DarkRed = Bit(3),
        Green = Bit(4),
        DarkGreen = Bit(5),
        Yellow = Bit(6),
        DarkYellow = Bit(7),
        Blue = Bit(8),
        DarkBlue = Bit(9),
        Magenta = Bit(10),
        DarkMagenta = Bit(11),
        Cyan = Bit(12),
        DarkCyan = Bit(13),
        Gray = Bit(14),
        DarkGray = Bit(15),
        White = Bit(16)
    };

    extern Int_t AsColor(Color color);

    class Terminal {
    public:
        static Int_t AsColor(Color color);
    };
};

#if defined(_WIN32)
    #include "Win32/TerminalWin32.hpp"
#elif defined(__unix__)
    #include "Posix/TerminalPosix.hpp"
#endif