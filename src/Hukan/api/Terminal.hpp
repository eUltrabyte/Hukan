#pragma once

#include "../core/Core.hpp"

namespace hk {
    namespace Terminal {
        enum HK_API ColorList {
            Reset = Bit(0),
            Red,
            DarkRed,
            Green,
            DarkGreen,
            Yellow,
            DarkYellow,
            Blue,
            DarkBlue,
            Magenta,
            DarkMagenta,
            Cyan,
            DarkCyan,
            Gray,
            White
        };

        class HK_API Color {
        public:
            Color() = default;
            Color(Uint_t color) : mColor(color) { }

            virtual ~Color() {
                delete this;
            }

            static void UseColor(ColorList color) HK_NOEXCEPT {
                #if defined(HUKAN_SYSTEM_WIN32)
                    static HANDLE sConsole = GetStdHandle(STD_OUTPUT_HANDLE);

                    switch(color) {
                        case ColorList::Reset:
                            SetConsoleTextAttribute(sConsole, 7);
                            break;

                        case ColorList::Red:
                            SetConsoleTextAttribute(sConsole, 12);
                            break;

                        case ColorList::DarkRed:
                            SetConsoleTextAttribute(sConsole, 4);
                            break;

                        case ColorList::Green:
                            SetConsoleTextAttribute(sConsole, 10);
                            break;

                        case ColorList::DarkGreen:
                            SetConsoleTextAttribute(sConsole, 2);
                            break;

                        case ColorList::Yellow:
                            SetConsoleTextAttribute(sConsole, 14);
                            break;

                        case ColorList::DarkYellow:
                            SetConsoleTextAttribute(sConsole, 6);
                            break;

                        case ColorList::Blue:
                            SetConsoleTextAttribute(sConsole, 9);
                            break;

                        case ColorList::DarkBlue:
                            SetConsoleTextAttribute(sConsole, 1);
                            break;

                        case ColorList::Magenta:
                            SetConsoleTextAttribute(sConsole, 13);
                            break;

                        case ColorList::DarkMagenta:
                            SetConsoleTextAttribute(sConsole, 5);
                            break;

                        case ColorList::Cyan:
                            SetConsoleTextAttribute(sConsole, 11);
                            break;

                        case ColorList::DarkCyan:
                            SetConsoleTextAttribute(sConsole, 3);
                            break;

                        case ColorList::Gray:
                            SetConsoleTextAttribute(sConsole, 8);
                            break;

                        case ColorList::White:
                            SetConsoleTextAttribute(sConsole, 15);
                            break;
                        
                    }
                #elif defined(HUKAN_SYSTEM_POSIX)
                    std::string _format = "";
                    switch(color) {
                        case ColorList::Reset:
                            _format = "\x1B[" + std::to_string(0) + "m";
                            printf("%s", _format.c_str());
                            break;

                        case ColorList::Red:
                            _format = "\x1B[" + std::to_string(91) + "m";
                            printf("%s", _format.c_str());
                            break;

                        case ColorList::DarkRed:
                            _format = "\x1B[" + std::to_string(31) + "m";
                            printf("%s", _format.c_str());
                            break;

                        case ColorList::Green:
                            _format = "\x1B[" + std::to_string(92) + "m";
                            printf("%s", _format.c_str());
                            break;

                        case ColorList::DarkGreen:
                            _format = "\x1B[" + std::to_string(32) + "m";
                            printf("%s", _format.c_str());
                            break;

                        case ColorList::Yellow:
                            _format = "\x1B[" + std::to_string(93) + "m";
                            printf("%s", _format.c_str());
                            break;

                        case ColorList::DarkYellow:
                            _format = "\x1B[" + std::to_string(33) + "m";
                            printf("%s", _format.c_str());
                            break;

                        case ColorList::Blue:
                            _format = "\x1B[" + std::to_string(94) + "m";
                            printf("%s", _format.c_str());
                            break;

                        case ColorList::DarkBlue:
                            _format = "\x1B[" + std::to_string(34) + "m";
                            printf("%s", _format.c_str());
                            break;

                        case ColorList::Magenta:
                            _format = "\x1B[" + std::to_string(95) + "m";
                            printf("%s", _format.c_str());
                            break;

                        case ColorList::DarkMagenta:
                            _format = "\x1B[" + std::to_string(35) + "m";
                            printf("%s", _format.c_str());
                            break;

                        case ColorList::Cyan:
                            _format = "\x1B[" + std::to_string(96) + "m";
                            printf("%s", _format.c_str());
                            break;

                        case ColorList::DarkCyan:
                            _format = "\x1B[" + std::to_string(36) + "m";
                            printf("%s", _format.c_str());
                            break;

                        case ColorList::Gray:
                            _format = "\x1B[" + std::to_string(30) + "m";
                            printf("%s", _format.c_str());
                            break;

                        case ColorList::White:
                            _format = "\x1B[" + std::to_string(37) + "m";
                            printf("%s", _format.c_str());
                            break;
                        
                    }
                #endif
            }

            HK_NODISCARD static std::vector<Uint_t> GetAvailableColors() HK_NOEXCEPT {
                std::vector<Uint_t> _colors;
                for(auto i = 0; i < 16; ++i) {
                    _colors.push_back(i);
                }
                return _colors;
            }

            HK_NODISCARD Uint_t& GetColor() HK_NOEXCEPT {
                return (Uint_t&)mColor;
            }

        private:
            Uint_t mColor;

        };
    };
};