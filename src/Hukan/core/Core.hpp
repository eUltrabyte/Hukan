#pragma once

#if defined(_WIN32)
    #define HUKAN_SYSTEM_WIN32
#elif defined(__unix__)
    #define HUKAN_SYSTEM_POSIX
#else
    #error "Hukan: Operating System Not Supported"
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
#include "utils/Vec2.hpp"
#include "utils/Vec3.hpp"
#include "utils/Vec4.hpp"
#include "utils/Mat4x4.hpp"

#define HK_MAKE_VERSION(major, minor, patch) ((((hk::Uint_t)(major)) << 22) | (((hk::Uint_t)(minor)) << 12) | ((hk::Uint_t)(patch)))
#define HK_VERSION_MAJOR(version) ((hk::Uint_t)(version) >> 22)
#define HK_VERSION_MINOR(version) (((hk::Uint_t)(version) >> 12) & 0x3ff)
#define HK_VERSION_PATCH(version) ((hk::Uint_t)(version) & 0xfff)

#if defined(HUKAN_DEBUG)
    #define HK_ENABLE_VALIDATION_LAYERS

    namespace hk {
        extern const std::vector<const Char_t*> g_validationLayers;
    };
#endif

#include "../api/Platform.hpp"
#include "../api/Terminal.hpp"
#include "../api/Logger.hpp"

#include "Assert.hpp"
