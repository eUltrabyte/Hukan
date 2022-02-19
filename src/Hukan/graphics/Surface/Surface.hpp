#pragma once

#include "../../core/Core.hpp"
#include "../../core/PhysicalDevice.hpp"

namespace hk {
    struct HK_API SurfaceCapabilities {
    public:
        Uint_t minImageCount;
        Uint_t maxImageCount;
        Vec2u currentExtent;
        Vec2u minImageExtent;
        Vec2u maxImageExtent;
        Uint_t maxImageArrayLayers;
        Uint_t supportedTransforms;
        Uint_t currentTransform;
        Uint_t supportedCompositeAlpha;
        Uint_t supportedUsageFlags;

    public:
        SurfaceCapabilities() {
            minImageCount = 0;
            maxImageCount = 1;
            currentExtent = { 0, 0 };
            minImageExtent = { 0, 0 };
            maxImageExtent = { 1, 1 };
            maxImageArrayLayers = 1;
            supportedTransforms = 0;
            currentTransform = 0;
            supportedCompositeAlpha = 0;
            supportedUsageFlags = 0;
        }
    };

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

    extern HK_NODISCARD void HK_API GetSurfaceCapabilities(PhysicalDevice* physicalDevice, Surface* surface, SurfaceCapabilities* capabilities) HK_NOEXCEPT;
};

#if defined(HUKAN_SYSTEM_WIN32)
    #include "Win32/SurfaceWin32.hpp"
#elif defined(HUKAN_SYSTEM_POSIX)
    #include "Posix/SurfacePosix.hpp"
#endif