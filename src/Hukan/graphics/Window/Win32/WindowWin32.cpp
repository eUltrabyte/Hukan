#include "WindowWin32.hpp"

#if defined(HUKAN_SYSTEM_WIN32)
#include <Windows.h>

namespace hk {
    LRESULT CALLBACK HK_API WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        switch(msg) {
            case WM_CLOSE:
                DestroyWindow(hwnd);
                break;

            case WM_DESTROY:
                DestroyWindow(hwnd);
                PostQuitMessage(0);
                std::quick_exit(0);
                break;

            default:
                return DefWindowProc(hwnd, msg, wParam, lParam);
        }
        return 0;
    }

    WindowImplWin32::WindowImplWin32(WindowCreateInfo* pWindowCreateInfo) {
        SetWindowCreateInfo(pWindowCreateInfo);
        mHinstance = GetModuleHandle(0);
        Create();
    }
    
    WindowImplWin32::~WindowImplWin32() {
        Destroy();
        delete this;
    }

    void WindowImplWin32::Create() {
        WNDCLASSEX windowClassEx;

        windowClassEx.cbSize = sizeof(WNDCLASSEX);
        windowClassEx.style = 0;
        windowClassEx.lpfnWndProc = WindowProc;
        windowClassEx.cbClsExtra = 0;
        windowClassEx.cbWndExtra = 0;
        windowClassEx.hInstance = mHinstance;
        windowClassEx.hIcon = 0;
        windowClassEx.hCursor = LoadCursor(0, IDC_ARROW);
        windowClassEx.hbrBackground = (HBRUSH)(COLOR_WINDOW + 5);
        windowClassEx.lpszMenuName = 0;
        windowClassEx.lpszClassName = "Hukan Win32 Window Class";
        windowClassEx.hIconSm = 0;

        if(!RegisterClassEx(&windowClassEx)) {
            Logger::Log(LoggerSeriousness::Error, "Win32 Window Registration Failed!");
        }

        RECT windowRect;
        windowRect.left = 50;
        windowRect.top = 50;
        windowRect.right = windowRect.left + mpWindowCreateInfo->width + 4;
        windowRect.bottom = windowRect.top + mpWindowCreateInfo->height + 4;

        UINT windowStyles = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

        AdjustWindowRectEx(&windowRect, windowStyles, 0, 0);

        mHwnd = CreateWindowEx(WS_EX_CLIENTEDGE, "Hukan Win32 Window Class", mpWindowCreateInfo->title, windowStyles, windowRect.left, windowRect.top, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, 0, 0, mHinstance, 0);
        if(!mHwnd) {
            Logger::Log(LoggerSeriousness::Error, "Win32 Window Creation Failed!");
        }

        ShowWindow(mHwnd, SW_SHOW);
        UpdateWindow(mHwnd);
    }

    void WindowImplWin32::Update() {
        if(PeekMessage(&mMessage, 0, 0, 0, PM_REMOVE)) {
            TranslateMessage(&mMessage);
            DispatchMessage(&mMessage);
        }
    }
    
    void WindowImplWin32::Destroy() {
        DestroyWindow(mHwnd);
    }

    void WindowImplWin32::SetWindowCreateInfo(WindowCreateInfo* pWindowCreateInfo) {
        mpWindowCreateInfo = pWindowCreateInfo;
    }

    WindowCreateInfo* WindowImplWin32::GetWindowCreateInfo() {
        return mpWindowCreateInfo;
    }

    HINSTANCE* WindowImplWin32::GetHINSTANCE() {
        return &mHinstance;
    }
    
    HWND* WindowImplWin32::GetHWND() {
        return &mHwnd;
    }
};

#endif