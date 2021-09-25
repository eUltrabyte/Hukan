#include "Clock.hpp"

namespace hk {
    Clock::Clock() { }
    
    Clock::~Clock() {
        delete this;
    }

    std::tm* Clock::GetActualTime() {
        std::time_t _time = std::time(0);
        std::tm* _now = std::localtime(&_time);
        return _now;
    }
};