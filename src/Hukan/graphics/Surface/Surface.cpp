#include "Surface.hpp"

namespace hk {
    Surface::Surface() { }
    
    Surface::~Surface() {
        delete this;
    }

    void Surface::SetVkInstance(VkInstance* pVkInstance) {
        mpVkInstance = pVkInstance;
    }

    VkInstance* Surface::GetVkInstance() HK_NOEXCEPT {
        return mpVkInstance;
    }
};