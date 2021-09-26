#include "../Platform.hpp"

#if defined(HUKAN_SYSTEM_POSIX)
#include <unistd.h>

namespace hk {
    void PosixWait(const Uint_t& microseconds) {
        usleep(microseconds);
    }

    void Wait(const Uint_t& microseconds) {
        PosixWait(microseconds);
    }
};

#endif