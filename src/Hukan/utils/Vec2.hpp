#pragma once

#include "../Hukan.hpp"

namespace hk {
    template<typename T>
    struct Vec2 {
    public:
        static_assert(std::is_arithmetic_v<T>, "Hukan Vec2<T> Is Not Arithmetic As Expected.");
        T x;
        T y;

        Vec2() = default;

        Vec2(T x0, T y0) {
            x = x0;
            y = y0;
        }

        template<typename U>
        Vec2(const Vec2<U>& vec) {
            x = static_cast<T>(vec.x);
            y = static_cast<T>(vec.y);
        }

        Vec2<T> operator+=(const T& value) HK_NOEXCEPT {
            return Vec2<T>(x += value, y += value);
        }

        Vec2<T> operator-=(const T& value) HK_NOEXCEPT {
            return Vec2<T>(x -= value, y -= value);
        }

        Vec2<T> operator*=(const T& value) HK_NOEXCEPT {
            return Vec2<T>(x *= value, y *= value);
        }

        Vec2<T> operator/=(const T& value) HK_NOEXCEPT {
            return Vec2<T>(x /= value, y /= value);
        }

        Vec2<T> operator+=(const Vec2<T>& vec) HK_NOEXCEPT {
            return Vec2<T>(x += vec.x, y += vec.y);
        }

        Vec2<T> operator-=(const Vec2<T>& vec) HK_NOEXCEPT {
            return Vec2<T>(x -= vec.x, y -= vec.y);
        }

        Vec2<T> operator*=(const Vec2<T>& vec) HK_NOEXCEPT {
            return Vec2<T>(x *= vec.x, y *= vec.y);
        }

        Vec2<T> operator/=(const Vec2<T>& vec) HK_NOEXCEPT {
            return Vec2<T>(x /= vec.x, y /= vec.y);
        }
    };

    using Vec2f = Vec2<Float_t>;
    using Vec2i = Vec2<Int_t>;
    using Vec2u = Vec2<Uint_t>;
    using Vec2l = Vec2<Long_t>;
    using Vec2d = Vec2<Double_t>;
};