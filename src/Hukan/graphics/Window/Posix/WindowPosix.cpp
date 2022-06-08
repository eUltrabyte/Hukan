#include "WindowPosix.hpp"

#if defined(HUKAN_SYSTEM_POSIX)

namespace hk {
    WindowImplPosix::WindowImplPosix(WindowCreateInfo* pWindowCreateInfo) {
        SetWindowCreateInfo(pWindowCreateInfo);
        Create();
    }
    
    WindowImplPosix::~WindowImplPosix() {
        Destroy();
        delete this;
    }

    void WindowImplPosix::Create() {
        mpDisplay = XOpenDisplay(nullptr);
        int _screen = DefaultScreen(mpDisplay);
        mWindow = XCreateSimpleWindow(mpDisplay, RootWindow(mpDisplay, _screen), 10, 10, mpWindowCreateInfo->width, mpWindowCreateInfo->height, 1, BlackPixel(mpDisplay, _screen), WhitePixel(mpDisplay, _screen));
        XStoreName(mpDisplay, mWindow, mpWindowCreateInfo->title);
        XSelectInput(mpDisplay, mWindow, ExposureMask | KeyPressMask | KeyReleaseMask);
        XMapWindow(mpDisplay, mWindow);
        XFlush(mpDisplay);
    }

    void WindowImplPosix::Update() {
        XSendEvent(mpDisplay, mWindow, 0, ExposureMask, &mEvent);
        XNextEvent(mpDisplay, &mEvent);
    }
    
    void WindowImplPosix::Destroy() {
        XCloseDisplay(mpDisplay);
    }

    void WindowImplPosix::SetWindowCreateInfo(WindowCreateInfo* pWindowCreateInfo) {
        mpWindowCreateInfo = pWindowCreateInfo;
    }

    WindowCreateInfo* WindowImplPosix::GetWindowCreateInfo() {
        return mpWindowCreateInfo;
    }

    Display* WindowImplPosix::GetDisplay() {
        return mpDisplay;
    }
    
    ::Window* WindowImplPosix::GetWindow() {
        return &mWindow;
    }

    bool WindowImplPosix::GetKeyState(int sign) {
        // TODO
        return false;
    }
};

#endif