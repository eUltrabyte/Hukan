#include "Hukan.hpp"

namespace hk {
    #if defined(HUKAN_SYSTEM_WIN32)
        const std::vector<const char*> g_validationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };
    #elif defined(HUKAN_SYSTEM_POSIX)
        const std::vector<const char*> g_validationLayers = {
            "VK_LAYER_LUNARG_standard_validation"
        };
    #endif
};