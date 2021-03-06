#pragma once

#include "Core.hpp"

namespace hk {
    extern void Assert();
};

#if defined(HUKAN_DEBUG)
    #define HK_DEBUG_BREAK(line, file) hk::Debugbreak(line, file);
#else
    #define HK_DEBUG_BREAK(line, file)
#endif

#define HK_ASSERT_MESSAGE() hk::Assert();
#define HK_ASSERT(value) if(value < 0) { HK_ASSERT_MESSAGE(); }
#define HK_ASSERT_VK(value) if(value != VK_SUCCESS) { HK_ASSERT_MESSAGE(); }