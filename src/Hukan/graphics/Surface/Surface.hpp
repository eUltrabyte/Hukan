#pragma once

#include "../../Hukan.hpp"

namespace hk {
    class HK_API Surface { };
};

#if defined(HUKAN_SYSTEM_WIN32)
    #include "Win32/SurfaceWin32.hpp"
#elif defined(HUKAN_SYSTEM_POSIX)
    // TODO for Posix
#endif