#include "Core.hpp"

namespace hk {
    #if defined(HK_ENABLE_VALIDATION_LAYERS)
        const std::vector<const char*> g_validationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };
    #endif
};
