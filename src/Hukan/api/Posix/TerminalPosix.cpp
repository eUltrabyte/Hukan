#include "TerminalPosix.hpp"

#if defined(__unix__)
namespace hk {
    Int_t PosixAsColor(Color color) {
        switch(color) {
            case Color::Reset:
                return Bit(0);
                break;

            case Color::Black:
                return Bit(1);
                break;

            case Color::Red:
                return Bit(2);
                break;

            case Color::DarkRed:
                return Bit(3);
                break;

            case Color::Green:
                return Bit(4);
                break;

            case Color::DarkGreen:
                return Bit(5);
                break;

            case Color::Yellow:
                return Bit(6);
                break;

            case Color::DarkYellow:
                return Bit(7);
                break;

            case Color::Blue:
                return Bit(8);
                break;

            case Color::DarkBlue:
                return Bit(9);
                break;

            case Color::Magenta:
                return Bit(10);
                break;

            case Color::DarkMagenta:
                return Bit(11);
                break;

            case Color::Cyan:
                return Bit(12);
                break;

            case Color::DarkCyan:
                return Bit(13);
                break;

            case Color::Gray:
                return Bit(14);
                break;

            case Color::DarkGray:
                return Bit(15);
                break;

            case Color::White:
                return Bit(16);
                break;
        }
    }

    Int_t AsColor(Color color) {
        return PosixAsColor(color);
    }
};
#endif