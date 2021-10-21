#include "WindowWin32.hpp"

#if defined(HUKAN_SYSTEM_WIN32)
#include <Windows.h>

namespace hk {
    LRESULT CALLBACK HK_API WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        switch(msg) {
            case WM_CLOSE:
                PostQuitMessage(0);
                DestroyWindow(hwnd);
                break;

            case WM_DESTROY:
                PostQuitMessage(0);
                DestroyWindow(hwnd);
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

        mHwnd = CreateWindowEx(WS_EX_CLIENTEDGE, "Hukan Win32 Window Class", mpWindowCreateInfo->title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, mpWindowCreateInfo->width, mpWindowCreateInfo->height, 0, 0, mHinstance, 0);
        if(!mHwnd) {
            Logger::Log(LoggerSeriousness::Error, "Win32 Window Creation Failed!");
        }

        ShowWindow(mHwnd, SW_SHOW);
    }

    void WindowImplWin32::Update() {
        UpdateWindow(mHwnd);

        while(GetMessage(&mMessage, 0, 0, 0) > 0) {
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