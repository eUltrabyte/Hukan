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

        void Create();
        void Destroy();

        void SetWindowCreateInfo(WindowCreateInfo* pWindowCreateInfo = nullptr);

    private:

    };
};