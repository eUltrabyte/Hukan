#pragma once

#include "../Hukan.hpp"

namespace hk {
    template<typename T>
    struct Vec3 {
    public:
        static_assert(std::is_arithmetic_v<T>, "Hukan Vec3<T> Is Not Arithmetic As Expected.");
        T x;
        T y;
        T z;

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
};