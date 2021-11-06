#include "SurfaceWin32.hpp"

#if defined(HUKAN_SYSTEM_WIN32)

namespace hk {
    SurfaceWin32::SurfaceWin32(VkInstance* pVkInstance, SurfaceWin32CreateInfo* pSurfaceCreateInfo) {
        SetVkInstance(pVkInstance);
        SetVkSurface(new VkSurfaceKHR());
        SetSurfaceCreateInfo(pSurfaceCreateInfo);
        Create();
    }

    SurfaceWin32::~SurfaceWin32() {
        Destroy();
        delete this;
    }

    void SurfaceWin32::Create() {
        VkResult _result = vkCreateWin32SurfaceKHR(*GetVkInstance(), mpSurfaceCreateInfo->GetVkWin32SurfaceCreateInfoKHR(), nullptr, GetVkSurfaceKHR());
        HK_ASSERT_VK(_result);
    }

    void SurfaceWin32::Destroy() {
        vkDestroySurfaceKHR(*GetVkInstance(), *GetVkSurfaceKHR(), nullptr);
    }

    void SurfaceWin32::SetSurfaceCreateInfo(SurfaceWin32CreateInfo* pSurfaceCreateInfo) {
        mpSurfaceCreateInfo = pSurfaceCreateInfo;
    }

    SurfaceWin32CreateInfo* SurfaceWin32::GetSurfaceCreateInfo() HK_NOEXCEPT {
        return mpSurfaceCreateInfo;
    }
};

#endif