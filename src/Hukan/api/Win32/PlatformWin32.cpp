#include "../Platform.hpp"

#if defined(HUKAN_SYSTEM_WIN32)
#include <Windows.h>

namespace hk {
    void Win32Wait(const Uint_t& microseconds) {
        Sleep(microseconds / 1000);
    }

    void Wait(const Uint_t& microseconds) {
        Win32Wait(microseconds);
    }
};

#endif