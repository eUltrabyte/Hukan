#pragma once

#if defined(_WIN32)
    #define HUKAN_SYSTEM_WIN32
#elif defined(__unix__)
    #define HUKAN_SYSTEM_POSIX
#else
    #error "Hukan Not Supported"
#endif

#define HK_NODISCARD [[nodiscard]]
#define HK_NOEXCEPT noexcept

#include "hkpch.hpp"

#if defined(HUKAN_SYSTEM_WIN32)
    #define VK_USE_PLATFORM_WIN32_KHR
#elif defined(HUKAN_SYSTEM_POSIX)
    #define VK_USE_PLATFORM_XLIB_KHR
#endif

#include <vulkan/vulkan.h>

#include "core/Build.hpp"

#include "utils/Types.hpp"
#include "utils/Clock.hpp"

#include "api/Platform.hpp"
#include "api/Terminal.hpp"
#include "api/Logger.hpp"

#include "core/Assert.hpp"
#include "core/Instance.hpp"
#include "core/Messenger.hpp"
#include "core/Layer.hpp"
#include "core/Extension.hpp"
#include "core/PhysicalDevice.hpp"

#include "graphics/Window/Window.hpp"
#include "graphics/Surface/Surface.hpp"

#if defined(HUKAN_DEBUG)
    #define HK_ENABLE_VALIDATION_LAYERS false
#else
    #define HK_ENABLE_VALIDATION_LAYERS  true
#endif

namespace hk {
    extern const std::vector<const char*> g_validationLayers;
};