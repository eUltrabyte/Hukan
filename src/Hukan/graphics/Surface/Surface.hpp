#pragma once

#include "../../core/Core.hpp"

namespace hk {
    class HK_API Surface {
    public:
        Surface();
        virtual ~Surface();

        virtual void Create();
        virtual void Destroy();

        virtual void SetVkInstance(VkInstance* pVkInstance = nullptr);
        virtual void SetVkSurface(VkSurfaceKHR* pVkSurface = nullptr);

        HK_NODISCARD virtual VkInstance* GetVkInstance() HK_NOEXCEPT;
        HK_NODISCARD virtual VkSurfaceKHR* GetVkSurfaceKHR() HK_NOEXCEPT;
    
    private:
        VkInstance* mpVkInstance;
        VkSurfaceKHR* mpVkSurface;

    };
};

#if defined(HUKAN_SYSTEM_WIN32)
    #include "Win32/SurfaceWin32.hpp"
#elif defined(HUKAN_SYSTEM_POSIX)
    #include "Posix/SurfacePosix.hpp"
#endif