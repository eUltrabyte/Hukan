#pragma once

#include "../core/Core.hpp"

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

        Vec2<T> operator+(const Vec2<T>& vec) HK_NOEXCEPT {
            return Vec2<T>(x + vec.x, y + vec.y);
        }

        Vec2<T> operator-(const Vec2<T>& vec) HK_NOEXCEPT {
            return Vec2<T>(x - vec.x, y - vec.y);
        }

        Vec2<T> operator*(const Vec2<T>& vec) HK_NOEXCEPT {
            return Vec2<T>(x * vec.x, y * vec.y);
        }

        Vec2<T> operator/(const Vec2<T>& vec) HK_NOEXCEPT {
            return Vec2<T>(x / vec.x, y / vec.y);
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

    template<typename T>
    constexpr T DotProduct(const Vec2<T>& vec0, const Vec2<T>& vec1) {
        return vec0.x * vec1.x + vec0.y * vec1.y;
    }

    template<typename T>
    constexpr Vec2<T> CrossProduct(const Vec2<T>& vec0, const Vec2<T>& vec1) {
        Vec2<T> value;
        value.x = vec0.y * vec1.y - vec0.y * vec1.x;
        value.y = vec0.x * vec1.x - vec0.x * vec1.y;
        return value;
    }

    template<typename T>
    constexpr T Length(const Vec2<T>& vec) {
        return std::sqrt((vec.x * vec.x) + (vec.y * vec.y));
    }

    template<typename T>
    constexpr Vec2<T> Normalize(const Vec2<T>& vec) {
        T length = Length(vec);
        Vec2<T> value;
        value.x = vec.x / length;
        value.y = vec.y / length;
        return value;
    }

    template<typename T>
    constexpr Vec2<T> Rotate(const Vec2<T>& point, T angle) {
        const Vec2<T> coords = Vec2<T>(std::sin(angle), std::cos(angle));
        const Vec2<T> value = Vec2<T>(point.x * coords.x - point.y * coords.y, point.x * coords.y - point.y * coords.x);
        return value;
    }
};