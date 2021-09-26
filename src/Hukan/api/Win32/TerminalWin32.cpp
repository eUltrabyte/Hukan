#include "../Terminal.hpp"

#if defined(HUKAN_SYSTEM_WIN32)
#include <Windows.h>

namespace hk {
    static HANDLE s_console;

    void Win32AsColor(Color color) {
        if(!s_console) {
            s_console = GetStdHandle(STD_OUTPUT_HANDLE);
        }

        int _color;

        switch(color) {
            case Color::Reset:
                _color = 7;
                break;

            case Color::Red:
                _color = 12;
                break;

            case Color::DarkRed:
                _color = 4;
                break;

            case Color::Green:
                _color = 10;
                break;

            case Color::DarkGreen:
                _color = 2;
                break;

            case Color::Yellow:
                _color = 14;
                break;

            case Color::DarkYellow:
                _color = 6;
                break;

            case Color::Blue:
                _color = 9;
                break;

            case Color::DarkBlue:
                _color = 1;
                break;

            case Color::Magenta:
                _color = 13;
                break;

            case Color::DarkMagenta:
                _color = 5;
                break;

            case Color::Cyan:
                _color = 11;
                break;

            case Color::DarkCyan:
                _color = 3;
                break;

            case Color::Gray:
                _color = 8;
                break;

            case Color::White:
                _color = 15;
                break;
        }

        SetConsoleTextAttribute(s_console, _color);
    }

    void Win32AvailableColors() {
        if(!s_console) {
            s_console = GetStdHandle(STD_OUTPUT_HANDLE);
        }

        for(int i = 1; i < 255; ++i) {
            SetConsoleTextAttribute(s_console, i);
            std::cout << i << " - Test\n";
        }
    }

    void AsColor(Color color) { Win32AsColor(color); }
    void AvailableColors() { Win32AvailableColors(); }
};

#endif