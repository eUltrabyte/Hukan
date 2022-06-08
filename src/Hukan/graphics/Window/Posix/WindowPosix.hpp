#pragma once

#include "../Window.hpp"

#if defined(HUKAN_SYSTEM_POSIX)
#include <X11/X.h>
#include <X11/Xlib.h>

namespace hk {
    class HK_API WindowImplPosix : public Window {
    public:
        WindowImplPosix(WindowCreateInfo* pWindowCreateInfo = nullptr);
        virtual ~WindowImplPosix();

        virtual void Create();
        virtual void Update();
        virtual void Destroy();

        virtual void SetWindowCreateInfo(WindowCreateInfo* pWindowCreateInfo = nullptr);

        virtual WindowCreateInfo* GetWindowCreateInfo();
        virtual Display* GetDisplay();
        virtual ::Window* GetWindow();
        virtual bool GetKeyState(int sign);

    private:
        WindowCreateInfo* mpWindowCreateInfo;
        Display* mpDisplay;
        ::Window mWindow;
        XEvent mEvent;

    };
};

#endif