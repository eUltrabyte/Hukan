#include "Window.hpp"

namespace hk {
    Window::Window(WindowCreateInfo* pWindowCreateInfo) {
        SetWindowCreateInfo(pWindowCreateInfo);
    }
    
    Window::~Window() {
        delete this;
    }

    void Window::SetWindowCreateInfo(WindowCreateInfo* pWindowCreateInfo) {
        mpWindowCreateInfo = pWindowCreateInfo;
    }

    WindowCreateInfo* Window::GetWindowCreateInfo() {
        return mpWindowCreateInfo;
    }

    bool Window::GetKeyState(int sign) {
        return false;
    }
};