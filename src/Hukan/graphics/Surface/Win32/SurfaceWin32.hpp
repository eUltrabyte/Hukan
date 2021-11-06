#pragma once

#include "../Surface.hpp"

#if defined(HUKAN_SYSTEM_WIN32)
#include <Windows.h>

namespace hk {
    struct HK_API SurfaceWin32CreateInfo {
    public:
        const void* pNext;
        HINSTANCE* pHinstance;
        HWND* pHwnd;

    private:
        VkWin32SurfaceCreateInfoKHR pSurfaceCreateInfo;

    public:
        SurfaceWin32CreateInfo() {
            pNext = nullptr;
            pHinstance = nullptr;
            pHwnd = nullptr;
        }

        HK_NODISCARD VkWin32SurfaceCreateInfoKHR* GetVkWin32SurfaceCreateInfoKHR() {
            pSurfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
            pSurfaceCreateInfo.pNext = pNext;
            pSurfaceCreateInfo.flags = 0;
            pSurfaceCreateInfo.hinstance = *pHinstance;
            pSurfaceCreateInfo.hwnd = *pHwnd;
            return &pSurfaceCreateInfo;
        }

    };

    class HK_API SurfaceWin32 : public Surface {
    public:
        SurfaceWin32(VkInstance* pVkInstance = nullptr, SurfaceWin32CreateInfo* pSurfaceCreateInfo = nullptr);
        virtual ~SurfaceWin32();

        virtual void Create();
        virtual void Destroy();

        virtual void SetSurfaceCreateInfo(SurfaceWin32CreateInfo* pSurfaceCreateInfo = nullptr);

        HK_NODISCARD virtual SurfaceWin32CreateInfo* GetSurfaceCreateInfo() HK_NOEXCEPT;

    private:
        SurfaceWin32CreateInfo* mpSurfaceCreateInfo;

    };
};

#endif