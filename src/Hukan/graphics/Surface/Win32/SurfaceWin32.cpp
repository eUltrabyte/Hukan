#include "SurfaceWin32.hpp"

#if defined(HUKAN_SYSTEM_WIN32)

namespace hk {
    SurfaceWin32::SurfaceWin32(VkInstance* pVkInstance, SurfaceWin32CreateInfo* pSurfaceCreateInfo) {
        SetVkInstance(pVkInstance);
        SetSurfaceCreateInfo(pSurfaceCreateInfo);
        Create();
    }

    SurfaceWin32::~SurfaceWin32() {
        Destroy();
        delete this;
    }

    void SurfaceWin32::Create() {
        VkResult _result = vkCreateWin32SurfaceKHR(*mpVkInstance, mpSurfaceCreateInfo->GetVkWin32SurfaceCreateInfoKHR(), nullptr, &mSurface);
        HK_ASSERT(_result);
    }

    void SurfaceWin32::Destroy() {
        vkDestroySurfaceKHR(*mpVkInstance, mSurface, nullptr);
    }

    void SurfaceWin32::SetVkInstance(VkInstance* pVkInstance) {
        mpVkInstance = pVkInstance;
    }

    void SurfaceWin32::SetSurfaceCreateInfo(SurfaceWin32CreateInfo* pSurfaceCreateInfo) {
        mpSurfaceCreateInfo = pSurfaceCreateInfo;
    }

    VkInstance* SurfaceWin32::GetVkInstance() {
        return mpVkInstance;
    }

    SurfaceWin32CreateInfo* SurfaceWin32::GetSurfaceCreateInfo() {
        return mpSurfaceCreateInfo;
    }

    VkSurfaceKHR* SurfaceWin32::GetVkSurfaceKHR() {
        return &mSurface;
    }
};

#endif