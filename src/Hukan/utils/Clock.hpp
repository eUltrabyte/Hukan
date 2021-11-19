#pragma once

#include "../core/Core.hpp"

namespace hk {
    class HK_API Clock {
    public:
        Clock();
        virtual ~Clock();

        virtual void Restart();

        HK_NODISCARD static std::tm* HK_API GetActualTime();

        HK_NODISCARD virtual std::chrono::time_point<std::chrono::steady_clock>* GetStartPoint();

    private:
        std::chrono::time_point<std::chrono::steady_clock> mStartPoint;

    };
};