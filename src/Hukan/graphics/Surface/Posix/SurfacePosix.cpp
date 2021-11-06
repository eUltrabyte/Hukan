#include "SurfacePosix.hpp"

#if defined(HUKAN_SYSTEM_POSIX)

namespace hk {
    SurfacePosix::SurfacePosix(VkInstance* pVkInstance, SurfacePosixCreateInfo* pSurfaceCreateInfo) {
        SetVkInstance(pVkInstance);
        SetSurfaceCreateInfo(pSurfaceCreateInfo);
        Create();
    }

    SurfacePosix::~SurfacePosix() {
        Destroy();
        delete this;
    }

    void SurfacePosix::Create() {
        VkResult _result = vkCreateXlibSurfaceKHR(*mpVkInstance, mpSurfaceCreateInfo->GetVkXlibSurfaceCreateInfoKHR(), nullptr, &mSurface);
        HK_ASSERT_VK(_result);
    }

    void SurfacePosix::Destroy() {
        vkDestroySurfaceKHR(*mpVkInstance, mSurface, nullptr);
    }

    void SurfacePosix::SetVkInstance(VkInstance* pVkInstance) {
        mpVkInstance = pVkInstance;
    }

    void SurfacePosix::SetSurfaceCreateInfo(SurfacePosixCreateInfo* pSurfaceCreateInfo) {
        mpSurfaceCreateInfo = pSurfaceCreateInfo;
    }

    VkInstance* SurfacePosix::GetVkInstance() {
        return mpVkInstance;
    }

    SurfacePosixCreateInfo* SurfacePosix::GetSurfaceCreateInfo() {
        return mpSurfaceCreateInfo;
    }

    VkSurfaceKHR* SurfacePosix::GetVkSurfaceKHR() {
        return &mSurface;
    }
};

#endif