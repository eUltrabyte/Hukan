#include "SurfacePosix.hpp"

#if defined(HUKAN_SYSTEM_POSIX)

namespace hk {
    SurfacePosix::SurfacePosix(VkInstance* pVkInstance, SurfacePosixCreateInfo* pSurfaceCreateInfo) {
        SetVkInstance(pVkInstance);
        SetVkSurface(new VkSurfaceKHR());
        SetSurfaceCreateInfo(pSurfaceCreateInfo);
        Create();
    }

    SurfacePosix::~SurfacePosix() {
        Destroy();
        delete this;
    }

    void SurfacePosix::Create() {
        VkResult _result = vkCreateXlibSurfaceKHR(*GetVkInstance(), mpSurfaceCreateInfo->GetVkXlibSurfaceCreateInfoKHR(), nullptr, GetVkSurfaceKHR());
        HK_ASSERT_VK(_result);
    }

    void SurfacePosix::Destroy() {
        vkDestroySurfaceKHR(*GetVkInstance(), *GetVkSurfaceKHR(), nullptr);
    }

    void SurfacePosix::SetSurfaceCreateInfo(SurfacePosixCreateInfo* pSurfaceCreateInfo) {
        mpSurfaceCreateInfo = pSurfaceCreateInfo;
    }

    SurfacePosixCreateInfo* SurfacePosix::GetSurfaceCreateInfo() HK_NOEXCEPT {
        return mpSurfaceCreateInfo;
    }
};

#endif