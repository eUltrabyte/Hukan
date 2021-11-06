#pragma once

#include "../Surface.hpp"

#if defined(HUKAN_SYSTEM_POSIX)
#include <X11/X.h>
#include <X11/Xlib.h>

namespace hk {
    struct HK_API SurfacePosixCreateInfo {
    public:
        const void* pNext;
        Display* pDisplay;
        ::Window* pWindow;

    private:
        VkXlibSurfaceCreateInfoKHR pSurfaceCreateInfo;

    public:
        SurfacePosixCreateInfo() {
            pNext = nullptr;
            pDisplay = nullptr;
            pWindow = nullptr;
        }

        HK_NODISCARD VkXlibSurfaceCreateInfoKHR* GetVkXlibSurfaceCreateInfoKHR() {
            pSurfaceCreateInfo.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
            pSurfaceCreateInfo.pNext = pNext;
            pSurfaceCreateInfo.flags = 0;
            pSurfaceCreateInfo.dpy = pDisplay;
            pSurfaceCreateInfo.window = *pWindow;
            return &pSurfaceCreateInfo;
        }

    };

    class HK_API SurfacePosix : public Surface {
    public:
        SurfacePosix(VkInstance* pVkInstance = nullptr, SurfacePosixCreateInfo* pSurfaceCreateInfo = nullptr);
        virtual ~SurfacePosix();

        virtual void Create();
        virtual void Destroy();

        virtual void SetSurfaceCreateInfo(SurfacePosixCreateInfo* pSurfaceCreateInfo = nullptr);

        HK_NODISCARD virtual SurfacePosixCreateInfo* GetSurfaceCreateInfo() HK_NOEXCEPT;

    private:
        SurfacePosixCreateInfo* mpSurfaceCreateInfo;

    };
};

#endif