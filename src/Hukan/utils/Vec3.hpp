#pragma once

#include "../core/Core.hpp"

namespace hk {
    template<typename T>
    struct Vec3 {
    public:
        static_assert(std::is_arithmetic_v<T>, "Hukan Vec3<T> Is Not Arithmetic As Expected.");
        T x;
        T y;
        T z;

        Vec3() = default;

        Vec3(T x0, T y0, T z0) {
            x = x0;
            y = y0;
            z = z0;
        }

        template<typename U>
        Vec3(const Vec2<U>& vec, U z0) {
            x = static_cast<T>(vec.x);
            y = static_cast<T>(vec.y);
            z = static_cast<T>(z0);
        }

        template<typename U>
        Vec3(U x0, const Vec2<U>& vec) {
            x = static_cast<T>(x0);
            y = static_cast<T>(vec.x);
            z = static_cast<T>(vec.y);
        }

        template<typename U>
        Vec3(const Vec3<U>& vec) {
            x = static_cast<T>(vec.x);
            y = static_cast<T>(vec.y);
            z = static_cast<T>(vec.z);
        }

        Vec3<T> operator+(const Vec3<T>& vec) HK_NOEXCEPT {
            return Vec3<T>(x + vec.x, y + vec.y, z + vec.z);
        }

        Vec3<T> operator-(const Vec3<T>& vec) HK_NOEXCEPT {
            return Vec3<T>(x - vec.x, y - vec.y, z - vec.z);
        }

        Vec3<T> operator*(const Vec3<T>& vec) HK_NOEXCEPT {
            return Vec3<T>(x * vec.x, y * vec.y, z * vec.z);
        }

        Vec3<T> operator/(const Vec3<T>& vec) HK_NOEXCEPT {
            return Vec3<T>(x / vec.x, y / vec.y, z / vec.z);
        }

        Vec3<T> operator+=(const T& value) HK_NOEXCEPT {
            return Vec3<T>(x += value, y += value, z += value);
        }

        Vec3<T> operator-=(const T& value) HK_NOEXCEPT {
            return Vec3<T>(x -= value, y -= value, z -= value);
        }

        Vec3<T> operator*=(const T& value) HK_NOEXCEPT {
            return Vec3<T>(x *= value, y *= value, z *= value);
        }

        Vec3<T> operator/=(const T& value) HK_NOEXCEPT {
            return Vec3<T>(x /= value, y /= value, z /= value);
        }

        Vec3<T> operator+=(const Vec3<T>& vec) HK_NOEXCEPT {
            return Vec3<T>(x += vec.x, y += vec.y, z += vec.z);
        }

        Vec3<T> operator-=(const Vec3<T>& vec) HK_NOEXCEPT {
            return Vec3<T>(x -= vec.x, y -= vec.y, z -= vec.z);
        }

        Vec3<T> operator*=(const Vec3<T>& vec) HK_NOEXCEPT {
            return Vec3<T>(x *= vec.x, y *= vec.y, z *= vec.z);
        }

        Vec3<T> operator/=(const Vec3<T>& vec) HK_NOEXCEPT {
            return Vec3<T>(x /= vec.x, y /= vec.y, z /= vec.z);
        }
    };

    using Vec3f = Vec3<Float_t>;
    using Vec3i = Vec3<Int_t>;
    using Vec3u = Vec3<Uint_t>;
    using Vec3l = Vec3<Long_t>;
    using Vec3d = Vec3<Double_t>;

    template<typename T>
    constexpr T DotProduct(const Vec3<T>& vec0, const Vec3<T>& vec1) {
        return vec0.x * vec1.x + vec0.y * vec1.y + vec0.z * vec1.z;
    }

    template<typename T>
    constexpr Vec3<T> CrossProduct(const Vec3<T>& vec0, const Vec3<T>& vec1) {
        Vec3<T> value;
        value.x = vec0.y * vec1.z - vec0.z * vec1.y;
        value.y = vec0.z * vec1.x - vec0.x * vec1.z;
        value.z = vec0.x * vec1.y - vec0.y * vec1.x;
        return value;
    }

    template<typename T>
    constexpr T Length(const Vec3<T>& vec) {
        return std::sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
    }

    template<typename T>
    constexpr Vec3<T> Normalize(const Vec3<T>& vec) {
        T length = Length(vec);
        Vec3<T> value;
        value.x = vec.x / length;
        value.y = vec.y / length;
        value.z = vec.z / length;
        return value;
    }

    template<typename T>
    constexpr Vec3<T> Rotate(const Vec3<T>& point, const Vec3<T>& angle) {
        Vec3<T> coords = point;

        const Vec2<T> roll = Rotate<T>(Vec2<T>(point.x, point.y), angle.z);
        coords.x = roll.x;
        coords.y = roll.y;

        const Vec2<T> pitch = Rotate<T>(Vec2<T>(point.y, point.z), angle.x);
        coords.y = pitch.x;
        coords.z = pitch.y;

        const Vec2<T> yaw = Rotate<T>(Vec2<T>(point.x, point.z), angle.y);
        coords.x = yaw.x;
        coords.z = yaw.y;

        return coords;
    }
};