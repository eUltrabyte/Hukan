#pragma once

#if defined(_WIN32)
    #define HUKAN_SYSTEM_WIN32
#elif defined(__unix__)
    #define HUKAN_SYSTEM_POSIX
#else
    #error "Hukan Not Supported"
#endif

#include "hkpch.hpp"

#include "api/Build.hpp"
#include "utils/Types.hpp"

#include "api/Terminal.hpp"
#include "api/Logger.hpp"