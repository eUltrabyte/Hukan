#pragma once

#include "../Hukan.hpp"

namespace hk {
    namespace Platform {
        inline void HK_API Wait(const Uint_t& microseconds) {
            std::this_thread::sleep_for(std::chrono::microseconds(microseconds));
        }

        inline Uint_t HK_API GetHardwareConcurrency() {
            Uint_t _hardwareConcurrency = std::thread::hardware_concurrency();
            if(!_hardwareConcurrency) {
                _hardwareConcurrency = 1;
            }
            return _hardwareConcurrency;
        }

        inline Uint_t HK_API GetSupportedVulkanVersion() {
            Uint_t _instanceVersion = VK_API_VERSION_1_0;
            auto _func = PFN_vkEnumerateInstanceVersion(vkGetInstanceProcAddr(nullptr, "vkEnumerateInstanceVersion"));
            if(_func != nullptr) {
                _func(&_instanceVersion);
            }
            return _instanceVersion;
        }
    };
};