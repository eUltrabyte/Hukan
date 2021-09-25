#include "../Terminal.hpp"

#if defined(HUKAN_SYSTEM_POSIX)
namespace hk {
    void PosixAsColor(Color color) {
        switch(color) {
            case Color::Reset:
                std::cout << "Reset\n";
                break;

            case Color::Black:
                std::cout << "Black\n";
                break;

            case Color::Red:
                std::cout << "Red\n";
                break;

            case Color::DarkRed:
                std::cout << "DarkRed\n";
                break;

            case Color::Green:
                std::cout << "Green\n";
                break;

            case Color::DarkGreen:
                std::cout << "DarkGreen\n";
                break;

            case Color::Yellow:
                std::cout << "Yellow\n";
                break;

            case Color::DarkYellow:
                std::cout << "DarkYellow\n";
                break;

            case Color::Blue:
                std::cout << "Blue\n";
                break;

            case Color::DarkBlue:
                std::cout << "DarkBlue\n";
                break;

            case Color::Magenta:
                std::cout << "Magenta\n";
                break;

            case Color::DarkMagenta:
                std::cout << "DarkMagenta\n";
                break;

            case Color::Cyan:
                std::cout << "Cyan\n";
                break;

            case Color::DarkCyan:
                std::cout << "DarkCyan\n";
                break;

            case Color::Gray:
                std::cout << "Gray\n";
                break;

            case Color::DarkGray:
                std::cout << "DarkGray\n";
                break;

            case Color::White:
                std::cout << "White\n";
                break;
        }
    }

    void AsColor(Color color) { PosixAsColor(color); }
};
#endif