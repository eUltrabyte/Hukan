#pragma once

#include "../Window.hpp"

#define HUKAN_SYSTEM_WIN32
#if defined(HUKAN_SYSTEM_WIN32)
#include <Windows.h>

namespace hk {
    class WindowImpl {
    public:
        WindowImpl();
        virtual ~WindowImpl();

        virtual void Create();
        virtual void Destroy();

        HINSTANCE* GetHINSTANCE();
        HWND* GetHWND();

    private:
        HINSTANCE mHinstance;
        HWND mHwnd;

    };
};

#endif