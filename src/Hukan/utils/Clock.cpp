#include "Clock.hpp"

namespace hk {
    Clock::Clock() {
        mStartPoint = std::chrono::steady_clock::now();
    }
    
    Clock::~Clock() {
        delete this;
    }

    void Clock::Restart() {
        mStartPoint = std::chrono::steady_clock::now();
    }

    std::tm* Clock::GetActualTime() {
        std::time_t _time = std::time(0);
        std::tm* _now = std::localtime(&_time);
        return _now;
    }

    std::chrono::time_point<std::chrono::steady_clock>* Clock::GetStartPoint() {
        return &mStartPoint;
    }
};