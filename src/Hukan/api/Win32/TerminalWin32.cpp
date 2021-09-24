#include "TerminalWin32.hpp"

#if defined(_WIN32)
namespace hk {
    Int_t Win32AsColor(Color color) {
        if(color == Color::Reset) {
            return Bit(0);
        } else if(color == Color::Black) {
            return Bit(1);
        } else if(color == Color::Red) {
            std::cout << Bit(2) << "\n";
            return Bit(2);
        } else if(color == Color::DarkRed) {
            return Bit(3);
        } else if(color == Color::Green) {
            return Bit(4);
        } else if(color == Color::DarkGreen) {
            return Bit(5);
        } else if(color == Color::Yellow) {
            return Bit(6);
        } else if(color == Color::DarkYellow) {
            return Bit(7);
        } else if(color == Color::Blue) {
            return Bit(8);
        } else if(color == Color::DarkBlue) {
            return Bit(9);
        } else if(color == Color::Magenta) {
            return Bit(10);
        } else if(color == Color::DarkMagenta) {
            return Bit(11);
        } else if(color == Color::Cyan) {
            return Bit(12);
        } else if(color == Color::DarkCyan) {
            return Bit(13);
        } else if(color == Color::Gray) {
            return Bit(14);
        } else if(color == Color::DarkGray) {
            return Bit(15);
        } else if(color == Color::White) {
            return Bit(16);
        } else {
            return Bit(0);
        }

        /* switch(color) {
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
        } */
    }

    Int_t AsColor(Color color) {
        return Win32AsColor(color);
    }

    Int_t Terminal::AsColor(Color color) {
        return Win32AsColor(color);
    }
};
#endif