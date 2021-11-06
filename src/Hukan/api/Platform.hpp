#pragma once

#include "../Hukan.hpp"

namespace hk {
    namespace Platform {
        extern void HK_API Wait(const Uint_t& microseconds) HK_NOEXCEPT;
        HK_NODISCARD extern Uint_t HK_API GetHardwareConcurrency() HK_NOEXCEPT;
        HK_NODISCARD extern Uint_t HK_API GetSupportedVulkanVersion() HK_NOEXCEPT;
    };
};