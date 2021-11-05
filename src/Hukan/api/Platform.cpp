#include "Platform.hpp"

namespace hk {
    namespace Platform {
        void Wait(const Uint_t& microseconds) HK_NOEXCEPT {
            std::this_thread::sleep_for(std::chrono::microseconds(microseconds));
        }

        Uint_t GetHardwareConcurrency() HK_NOEXCEPT {
            Uint_t _hardwareConcurrency = std::thread::hardware_concurrency();
            if(!_hardwareConcurrency) {
                _hardwareConcurrency = 1;
            }
            return _hardwareConcurrency;
        }

        Uint_t GetSupportedVulkanVersion() HK_NOEXCEPT {
            Uint_t _instanceVersion = VK_API_VERSION_1_0;
            auto _func = PFN_vkEnumerateInstanceVersion(vkGetInstanceProcAddr(nullptr, "vkEnumerateInstanceVersion"));
            if(_func != nullptr) {
                _func(&_instanceVersion);
            }
            return _instanceVersion;
        }
    };
};