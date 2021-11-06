#pragma once

#include "../Hukan.hpp"

namespace hk {
    template<typename T>
    struct Vec4 {
    public:
        static_assert(std::is_arithmetic_v<T>, "Hukan Vec4<T> Is Not Arithmetic As Expected.");
        Vec4(T x, T y, T z, T w) {
            mX = x;
            mY = y;
            mZ = z;
            mW = w;
        }

        template<typename U>
        Vec4(U x, U y, const Vec2<U>& vec) {
            mX = static_cast<T>(x);
            mY = static_cast<T>(y);
            mZ = static_cast<T>(vec.GetX());
            mW = static_cast<T>(vec.GetY());
        }

        template<typename U>
        Vec4(U x, const Vec2<U>& vec, U w) {
            mX = static_cast<T>(x);
            mY = static_cast<T>(vec.GetX());
            mZ = static_cast<T>(vec.GetY());
            mW = static_cast<T>(w);
        }

        template<typename U>
        Vec4(const Vec2<U>& vec, U z, U w) {
            mX = static_cast<T>(vec.GetX());
            mY = static_cast<T>(vec.GetY());
            mZ = static_cast<T>(z);
            mW = static_cast<T>(w);
        }

        template<typename U>
        Vec4(const Vec2<U>& vec0, const Vec2<U>& vec1) {
            mX = static_cast<T>(vec0.GetX());
            mY = static_cast<T>(vec0.GetY());
            mZ = static_cast<T>(vec1.GetX());
            mW = static_cast<T>(vec1.GetY());
        }

        template<typename U>
        Vec4(U x, const Vec3<U>& vec) {
            mX = static_cast<T>(x);
            mY = static_cast<T>(vec.GetX());
            mZ = static_cast<T>(vec.GetY());
            mW = static_cast<T>(vec.GetZ());
        }

        template<typename U>
        Vec4(const Vec3<U>& vec, U w) {
            mX = static_cast<T>(vec.GetX());
            mY = static_cast<T>(vec.GetY());
            mZ = static_cast<T>(vec.GetZ());
            mW = static_cast<T>(w);
        }

        template<typename U>
        Vec4(const Vec4<U>& vec) {
            mX = static_cast<T>(vec.GetX());
            mY = static_cast<T>(vec.GetY());
            mZ = static_cast<T>(vec.GetZ());
            mW = static_cast<T>(vec.GetW());
        }

        HK_NODISCARD T GetX() {
            return mX;
        }

        HK_NODISCARD T GetY() {
            return mY;
        }

        HK_NODISCARD T GetZ() {
            return mZ;
        }

        HK_NODISCARD T GetW() {
            return mW;
        }

        Vec4<T> operator+=(const T& value) HK_NOEXCEPT {
            return Vec4<T>(mX += value, mY += value, mZ += value, mW += value);
        }

        Vec4<T> operator-=(const T& value) HK_NOEXCEPT {
            return Vec4<T>(mX -= value, mY -= value, mZ -= value, mW -= value);
        }

        Vec4<T> operator*=(const T& value) HK_NOEXCEPT {
            return Vec4<T>(mX *= value, mY *= value, mZ *= value, mW *= value);
        }

        Vec4<T> operator/=(const T& value) HK_NOEXCEPT {
            return Vec4<T>(mX /= value, mY /= value, mZ /= value, mW /= value);
        }

        Vec4<T> operator+=(const Vec4<T>& vec) HK_NOEXCEPT {
            return Vec4<T>(mX += vec.mX, mY += vec.mY, mZ += vec.mZ, mW += vec.mW);
        }

        Vec4<T> operator-=(const Vec4<T>& vec) HK_NOEXCEPT {
            return Vec4<T>(mX -= vec.mX, mY -= vec.mY, mZ -= vec.mZ, mW -= vec.mW);
        }

        Vec4<T> operator*=(const Vec4<T>& vec) HK_NOEXCEPT {
            return Vec4<T>(mX *= vec.mX, mY *= vec.mY, mZ *= vec.mZ, mW *= vec.mW);
        }

        Vec4<T> operator/=(const Vec4<T>& vec) HK_NOEXCEPT {
            return Vec4<T>(mX /= vec.mX, mY /= vec.mY, mZ /= vec.mZ, mW /= vec.mW);
        }

    private:
        T mX;
        T mY;
        T mZ;
        T mW;

    };

    using Vec4f = Vec4<Float_t>;
    using Vec4i = Vec4<Int_t>;
    using Vec4u = Vec4<Uint_t>;
    using Vec4l = Vec4<Long_t>;
    using Vec4d = Vec4<Double_t>;
};