#pragma once

#include "../Hukan.hpp"

namespace hk {
    template<typename T>
    struct Vec3 {
    public:
        static_assert(std::is_arithmetic_v<T>, "Hukan Vec3<T> Is Not Arithmetic As Expected.");
        Vec3(T x, T y, T z) {
            mX = x;
            mY = y;
            mZ = z;
        }

        template<typename U>
        Vec3(const Vec2<U>& vec, U z) {
            mX = static_cast<T>(vec.GetX());
            mY = static_cast<T>(vec.GetY());
            mZ = static_cast<T>(z);
        }

        template<typename U>
        Vec3(U x, const Vec2<U>& vec) {
            mX = static_cast<T>(x);
            mY = static_cast<T>(vec.GetX());
            mZ = static_cast<T>(vec.GetY());
        }

        template<typename U>
        Vec3(const Vec3<U>& vec) {
            mX = static_cast<T>(vec.GetX());
            mY = static_cast<T>(vec.GetY());
            mZ = static_cast<T>(vec.GetZ());
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

    private:
        T mX;
        T mY;
        T mZ;

    };

    using Vec3f = Vec3<Float_t>;
    using Vec3i = Vec3<Int_t>;
    using Vec3u = Vec3<Uint_t>;
};