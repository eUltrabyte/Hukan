#pragma once

#include "../core/Core.hpp"

namespace hk {
    template<typename T>
    struct Vec4 {
    public:
        static_assert(std::is_arithmetic_v<T>, "Hukan Vec4<T> Is Not Arithmetic As Expected.");
        T x;
        T y;
        T z;
        T w;

        Vec4() = default;

        Vec4(T x0, T y0, T z0, T w0) {
            x = x0;
            y = y0;
            z = z0;
            w = w0;
        }

        template<typename U>
        Vec4(U x0, U y0, const Vec2<U>& vec) {
            x = static_cast<T>(x0);
            y = static_cast<T>(y0);
            z = static_cast<T>(vec.x);
            w = static_cast<T>(vec.y);
        }

        template<typename U>
        Vec4(U x0, const Vec2<U>& vec, U w0) {
            x = static_cast<T>(x0);
            y = static_cast<T>(vec.x);
            z = static_cast<T>(vec.y);
            w = static_cast<T>(w0);
        }

        template<typename U>
        Vec4(const Vec2<U>& vec, U z0, U w0) {
            x = static_cast<T>(vec.x);
            y = static_cast<T>(vec.y);
            z = static_cast<T>(z0);
            w = static_cast<T>(w0);
        }

        template<typename U>
        Vec4(const Vec2<U>& vec0, const Vec2<U>& vec1) {
            x = static_cast<T>(vec0.x);
            y = static_cast<T>(vec0.y);
            z = static_cast<T>(vec1.x);
            w = static_cast<T>(vec1.y);
        }

        template<typename U>
        Vec4(U x0, const Vec3<U>& vec) {
            x = static_cast<T>(x0);
            y = static_cast<T>(vec.x);
            z = static_cast<T>(vec.y);
            w = static_cast<T>(vec.z);
        }

        template<typename U>
        Vec4(const Vec3<U>& vec, U w0) {
            x = static_cast<T>(vec.x);
            y = static_cast<T>(vec.y);
            z = static_cast<T>(vec.z);
            w = static_cast<T>(w0);
        }

        template<typename U>
        Vec4(const Vec4<U>& vec) {
            x = static_cast<T>(vec.x);
            y = static_cast<T>(vec.y);
            z = static_cast<T>(vec.z);
            w = static_cast<T>(vec.w);
        }

        Vec4<T> operator+=(const T& value) HK_NOEXCEPT {
            return Vec4<T>(x += value, y += value, z += value, w += value);
        }

        Vec4<T> operator-=(const T& value) HK_NOEXCEPT {
            return Vec4<T>(x -= value, y -= value, z -= value, w -= value);
        }

        Vec4<T> operator*=(const T& value) HK_NOEXCEPT {
            return Vec4<T>(x *= value, y *= value, z *= value, w *= value);
        }

        Vec4<T> operator/=(const T& value) HK_NOEXCEPT {
            return Vec4<T>(x /= value, y /= value, z /= value, w /= value);
        }

        Vec4<T> operator+=(const Vec4<T>& vec) HK_NOEXCEPT {
            return Vec4<T>(x += vec.x, y += vec.y, z += vec.z, w += vec.w);
        }

        Vec4<T> operator-=(const Vec4<T>& vec) HK_NOEXCEPT {
            return Vec4<T>(x -= vec.x, y -= vec.y, z -= vec.z, w -= vec.w);
        }

        Vec4<T> operator*=(const Vec4<T>& vec) HK_NOEXCEPT {
            return Vec4<T>(x *= vec.x, y *= vec.y, z *= vec.z, w *= vec.w);
        }

        Vec4<T> operator/=(const Vec4<T>& vec) HK_NOEXCEPT {
            return Vec4<T>(x /= vec.x, y /= vec.y, z /= vec.z, w /= vec.w);
        }
    };

    using Vec4f = Vec4<Float_t>;
    using Vec4i = Vec4<Int_t>;
    using Vec4u = Vec4<Uint_t>;
    using Vec4l = Vec4<Long_t>;
    using Vec4d = Vec4<Double_t>;
};