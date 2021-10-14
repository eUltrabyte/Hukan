#include "WindowWin32.hpp"

#define HUKAN_SYSTEM_WIN32
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
                break;

            default:
                return DefWindowProc(hwnd, msg, wParam, lParam);
        }
        return 0;
    }

    WindowImpl::WindowImpl() {
        mHinstance = GetModuleHandle(0);
        Create();
    }
    
    WindowImpl::~WindowImpl() {
        Destroy();
        delete this;
    }

    void WindowImpl::Create() {
        WNDCLASSEX windowClassEx;
        MSG message;

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

        mHwnd = CreateWindowEx(WS_EX_CLIENTEDGE, "Hukan Win32 Window Class", "Hukan Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, 0, 0, mHinstance, 0);
        if(!mHwnd) {
            Logger::Log(LoggerSeriousness::Error, "Win32 Window Creation Failed!");
        }

        ShowWindow(mHwnd, SW_SHOW);
        UpdateWindow(mHwnd);

        while(GetMessage(&message, 0, 0, 0) > 0) {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
    }
    
    void WindowImpl::Destroy() {
        DestroyWindow(mHwnd);
    }

    HINSTANCE* WindowImpl::GetHINSTANCE() {
        return &mHinstance;
    }
    
    HWND* WindowImpl::GetHWND() {
        return &mHwnd;
    }
};

#endif