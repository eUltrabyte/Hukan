#include "Surface.hpp"

namespace hk {
    Surface::Surface() { }
    
    Surface::~Surface() {
        delete this;
    }

    void Surface::Create() { }
    
    void Surface::Destroy() { }

    void Surface::SetVkInstance(VkInstance* pVkInstance) {
        mpVkInstance = pVkInstance;
    }

    void Surface::SetVkSurface(VkSurfaceKHR* pVkSurface) {
        mpVkSurface = pVkSurface;
    }

    VkInstance* Surface::GetVkInstance() HK_NOEXCEPT {
        return mpVkInstance;
    }

    VkSurfaceKHR* Surface::GetVkSurfaceKHR() HK_NOEXCEPT {
        return mpVkSurface;
    }
};