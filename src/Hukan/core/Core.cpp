#include "Core.hpp"

namespace hk {
    #if defined(HUKAN_DEBUG)
        #if HK_ENABLE_VALIDATION_LAYERS == false
            const std::vector<const char*> g_validationLayers = {
                "VK_LAYER_KHRONOS_validation"
            };
        #endif
    #endif
};