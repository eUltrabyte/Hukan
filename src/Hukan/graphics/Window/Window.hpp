#pragma once

#include "../../Hukan.hpp"

namespace hk {
    struct HK_API WindowCreateInfo {
    public:
        const Char_t* title;
        uint16_t width;
        uint16_t height;

    public:
        WindowCreateInfo() {
            title = nullptr;
            width = 0;
            height = 0;
        }

    };

    class HK_API Window {
    public:
        Window(WindowCreateInfo* pWindowCreateInfo = nullptr);
        virtual ~Window();

        virtual void SetWindowCreateInfo(WindowCreateInfo* pWindowCreateInfo = nullptr);

        virtual WindowCreateInfo* GetWindowCreateInfo();

    private:
        WindowCreateInfo* mpWindowCreateInfo;

    };
};

#if defined(HUKAN_SYSTEM_WIN32)
    #include "Win32/WindowWin32.hpp"
#elif defined(HUKAN_SYSTEM_POSIX)
    // TODO for Posix
#endif