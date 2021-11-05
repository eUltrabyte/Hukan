#pragma once

#if defined(HUKAN_SYSTEM_WIN32)
    #include <Windows.h>
#elif defined(HUKAN_SYSTEM_POSIX)
    #include <unistd.h>
#endif

#include "../Hukan.hpp"

namespace hk {
    namespace Platform {
        inline void HK_API Wait(const Uint_t& microseconds) {
            #if defined(HUKAN_SYSTEM_WIN32)
                Sleep(microseconds / 1000);
            #elif defined(HUKAN_SYSTEM_POSIX)
                usleep(microseconds);
            #endif
        }
    };
};