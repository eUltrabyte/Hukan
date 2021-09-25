#include "../Terminal.hpp"

#if defined(HUKAN_SYSTEM_POSIX)
namespace hk {
    void PosixAsColor(Color color) {
        int _color;

        switch(color) {
            case Color::Reset:
                _color = 0;
                break;

            case Color::Red:
                _color = 91;
                break;

            case Color::DarkRed:
                _color = 31;
                break;

            case Color::Green:
                _color = 92;
                break;

            case Color::DarkGreen:
                _color = 32;
                break;

            case Color::Yellow:
                _color = 93;
                break;

            case Color::DarkYellow:
                _color = 33;
                break;

            case Color::Blue:
                _color = 94;
                break;

            case Color::DarkBlue:
                _color = 34;
                break;

            case Color::Magenta:
                _color = 95;
                break;

            case Color::DarkMagenta:
                _color = 35;
                break;

            case Color::Cyan:
                _color = 96;
                break;

            case Color::DarkCyan:
                _color = 36;
                break;

            case Color::Gray:
                _color = 30;
                break;

            case Color::White:
                _color = 37;
                break;
        }

        std::string _format;
        _format = "\u001b[" + std::to_string(_color) + "m";
        printf("%s", _format.c_str());
    }
    
    void PosixAvailableColors() {
        for(int i = 1; i < 255; ++i) {
            std::string _format;
            _format = "\x1B[" + std::to_string(i) + "m";
            printf("%i - %s", i, _format.c_str());
        }
    }

    void AsColor(Color color) { PosixAsColor(color); }
    void AvailableColors() { PosixAvailableColors(); }
};
#endif