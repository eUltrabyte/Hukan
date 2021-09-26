#pragma once

#if defined(_WIN32)
    #define HUKAN_SYSTEM_WIN32
#elif defined(__unix__)
    #define HUKAN_SYSTEM_POSIX
#else
    #error "Hukan Not Supported"
#endif

#include "hkpch.hpp"

#include <vulkan/vulkan.h>

#include "core/Build.hpp"

#include "utils/Types.hpp"
#include "utils/Clock.hpp"

#include "api/Platform.hpp"
#include "api/Terminal.hpp"
#include "api/Logger.hpp"

#include "core/Assert.hpp"
#include "core/Instance.hpp"