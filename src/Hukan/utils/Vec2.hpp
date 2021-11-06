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

        HK_NODISCARD T GetX() HK_NOEXCEPT {
            return mX;
        }

        HK_NODISCARD T GetY() HK_NOEXCEPT {
            return mY;
        }

        Vec2<T> operator+=(const T& value) HK_NOEXCEPT {
            return Vec2<T>(mX += value, mY += value);
        }

        Vec2<T> operator-=(const T& value) HK_NOEXCEPT {
            return Vec2<T>(mX -= value, mY -= value);
        }

        Vec2<T> operator*=(const T& value) HK_NOEXCEPT {
            return Vec2<T>(mX *= value, mY *= value);
        }

        Vec2<T> operator/=(const T& value) HK_NOEXCEPT {
            return Vec2<T>(mX /= value, mY /= value);
        }

        Vec2<T> operator+=(const Vec2<T>& vec) HK_NOEXCEPT {
            return Vec2<T>(mX += vec.mX, mY += vec.mY);
        }

        Vec2<T> operator-=(const Vec2<T>& vec) HK_NOEXCEPT {
            return Vec2<T>(mX -= vec.mX, mY -= vec.mY);
        }

        Vec2<T> operator*=(const Vec2<T>& vec) HK_NOEXCEPT {
            return Vec2<T>(mX *= vec.mX, mY *= vec.mY);
        }

        Vec2<T> operator/=(const Vec2<T>& vec) HK_NOEXCEPT {
            return Vec2<T>(mX /= vec.mX, mY /= vec.mY);
        }

    private:
        T mX;
        T mY;

    };

    using Vec2f = Vec2<Float_t>;
    using Vec2i = Vec2<Int_t>;
    using Vec2u = Vec2<Uint_t>;
    using Vec2l = Vec2<Long_t>;
    using Vec2d = Vec2<Double_t>;
};