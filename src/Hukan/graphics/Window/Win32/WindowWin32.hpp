#pragma once

#include "../Window.hpp"

#if defined(HUKAN_SYSTEM_WIN32)
#include <Windows.h>

namespace hk {
    class HK_API WindowImplWin32 : public Window {
    public:
        WindowImplWin32(WindowCreateInfo* pWindowCreateInfo = nullptr);
        virtual ~WindowImplWin32();

        virtual void Create();
        virtual void Update();
        virtual void Destroy();

        virtual void SetWindowCreateInfo(WindowCreateInfo* pWindowCreateInfo = nullptr);

        virtual WindowCreateInfo* GetWindowCreateInfo();
        virtual HINSTANCE* GetHINSTANCE();
        virtual HWND* GetHWND();
        virtual bool GetKeyState(int sign);

    private:
        WindowCreateInfo* mpWindowCreateInfo;
        HINSTANCE mHinstance;
        HWND mHwnd;
        MSG mMessage;

    };
};

#endif