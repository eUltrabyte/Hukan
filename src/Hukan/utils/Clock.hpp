#pragma once

#include "../Hukan.hpp"

namespace hk {
    class HK_API Clock {
    public:
        Clock();
        virtual ~Clock();

        static std::tm* HK_API GetActualTime();
    };
};