#pragma once

#include "../Hukan.hpp"

namespace hk {
    template<typename T>
    struct Vec2 {
    public:
        static_assert(std::is_arithmetic_v<T>, "Hukan Vec2<T> Is Not Arithmetic As Expected.");
        Vec2(T x, T y) {
            mX = x;
            mY = y;
        }

        template<typename U>
        Vec2(const Vec2<U>& vec) {
            mX = static_cast<T>(vec.GetX());
            mY = static_cast<T>(vec.GetY());
        }

        HK_NODISCARD T GetX() {
            return mX;
        }

        HK_NODISCARD T GetY() {
            return mY;
        }

    private:
        T mX;
        T mY;

    };

    using Vec2f = Vec2<Float_t>;
    using Vec2i = Vec2<Int_t>;
    using Vec2u = Vec2<Uint_t>;
};