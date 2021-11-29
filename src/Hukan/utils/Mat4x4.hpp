#pragma once

#include "../core/Core.hpp"

namespace hk {
    constexpr Double_t pi = 3.14159265359;

    template<typename T>
    constexpr T radians(T degrees) {
        return degrees / 180.0f * static_cast<T>(pi);
    }

    template<typename T>
    constexpr T degrees(T radians) {
        return radians * 180.0f / static_cast<T>(pi);
    }

    template<typename T>
    struct Mat4x4 {
    public:
        static_assert(std::is_arithmetic_v<T>, "Hukan Mat4x4<T> Is Not Arithmetic As Expected.");
        std::array<std::array<T, 4>, 4> matrix;

        Mat4x4() { Clear(); }

        Mat4x4(T fov, T aspectRatio, T zNear, T zFar) {
            Clear();
            T _halfFov = 1.0f / std::tan(1.0f * fov);
            matrix[0][0] = 1.0f / aspectRatio * _halfFov;
            matrix[1][1] = -(1.0f / _halfFov);
            matrix[2][2] = zFar / (zFar - zNear);
            matrix[2][3] = 1.0f;
            matrix[3][2] = -(2.0f * zFar * zNear) / (zFar - zNear);
        }

        Mat4x4(T left, T right, T bottom, T top, T zNear, T zFar) {
            Identity();
            matrix[0][0] = 2.0f / (right - left);
            matrix[1][1] = 2.0f / (bottom - top);
            matrix[2][2] = 1.0f / (zFar - zNear);
            matrix[3][0] = -(right + left) / (right - left);
            matrix[3][1] = -(bottom + top) / (bottom - top);
            matrix[3][2] = -zNear / (zFar - zNear);
        }

        void Clear() {
            matrix = { std::array<T, 4>{ 0, 0, 0, 0 }, std::array<T, 4>{ 0, 0, 0, 0 }, std::array<T, 4>{ 0, 0, 0, 0 }, std::array<T, 4>{ 0, 0, 0, 0 } };
        }

        void Identity() {
            matrix[0][0] = 1.0f;
            matrix[1][1] = 1.0f;
            matrix[2][2] = 1.0f;
            matrix[3][3] = 1.0f;
        }

        void SetMatrixAt(Int_t x, Int_t y, T data) {
            matrix[x][y] = data;
        }

        Mat4x4<T> operator*(const Mat4x4<T>& mat) {
            Mat4x4<T> _result;

            for(auto x = 0; x < 4; ++x) {
                for(auto y = 0; y < 4; ++y) {
                    for(auto z = 0; z < 4; ++z) {
                        _result.matrix[x][y] += mat.matrix[x][z] * matrix[z][y];
                    }
                }
            }

            return _result;
        }

        HK_NODISCARD T* GetMatrixAt(Int_t x, Int_t y) {
            return &matrix[x][y];
        }
    };

    using Mat4x4f = Mat4x4<Float_t>;
    using Mat4x4i = Mat4x4<Int_t>;
    using Mat4x4u = Mat4x4<Uint_t>;
    using Mat4x4l = Mat4x4<Long_t>;
    using Mat4x4d = Mat4x4<Double_t>;

    template<typename T>
    using Mat4 = Mat4x4<T>;

    using Mat4f = Mat4<Float_t>;
    using Mat4i = Mat4<Int_t>;
    using Mat4u = Mat4<Uint_t>;
    using Mat4l = Mat4<Long_t>;
    using Mat4d = Mat4<Double_t>;

    template<typename T>
    constexpr Mat4x4<T> Identity() {
        Mat4x4<T> _result;
        _result.matrix[0][0] = 1.0f;
        _result.matrix[1][1] = 1.0f;
        _result.matrix[2][2] = 1.0f;
        _result.matrix[3][3] = 1.0f;
        return _result;
    }

    template<typename T>
    constexpr Mat4x4<T> Projection(T fov, T aspectRatio, T zNear, T zFar) {
        return Mat4x4<T>(fov, aspectRatio, zNear, zFar);
    }

    template<typename T>
    constexpr Mat4x4<T> Ortho2D(T left, T right, T bottom, T top, T zNear, T zFar) {
        return Mat4x4<T>(left, right, bottom, top, zNear, zFar);
    }

    template<typename T>
    constexpr void Translate(Mat4x4<T>& mat, const Vec3<T>& vec) {
        mat.matrix[3][0] = mat.matrix[0][0] * vec.x + mat.matrix[1][0] * vec.y + mat.matrix[2][0] * vec.z + mat.matrix[3][0];
	    mat.matrix[3][1] = mat.matrix[0][1] * vec.x + mat.matrix[1][1] * vec.y + mat.matrix[2][1] * vec.z + mat.matrix[3][1];
        mat.matrix[3][2] = mat.matrix[0][2] * vec.x + mat.matrix[1][2] * vec.y + mat.matrix[2][2] * vec.z + mat.matrix[3][2];
	    mat.matrix[3][3] = mat.matrix[0][3] * vec.x + mat.matrix[1][3] * vec.y + mat.matrix[2][3] * vec.z + mat.matrix[3][3];
    }

    template<typename T>
    constexpr void Rotate(Mat4x4<T>& mat, T angle, const Vec3<T>& vec) {
        T _angleCos = std::cos(angle);
        T _angleSin = std::sin(angle);
        Vec3<T> _axis = Normalize(vec);
        Mat4x4<T> _result;

        _result.matrix[0][0] = _angleCos + (1.0f - _angleCos) * _axis.x * _axis.x;
        _result.matrix[0][1] = (1.0f - _angleCos) * _axis.x * _axis.y + _angleSin * _axis.z;
        _result.matrix[0][2] = (1.0f - _angleCos) * _axis.x * _axis.z + _angleSin * _axis.y;
        _result.matrix[0][3] = 0.0f;

        _result.matrix[1][0] = (1.0f - _angleCos) * _axis.y * _axis.x - _angleSin * _axis.z;
        _result.matrix[1][1] = _angleCos + (1.0f - _angleCos) * _axis.y * _axis.y;
        _result.matrix[1][2] = (1.0f - _angleCos) * _axis.y * _axis.z + _angleSin * _axis.x;
        _result.matrix[1][3] = 0.0f;

        _result.matrix[2][0] = (1.0f - _angleCos) * _axis.z * _axis.x + _angleSin * _axis.y;
        _result.matrix[2][1] = (1.0f - _angleCos) * _axis.z * _axis.y - _angleSin * _axis.x;
        _result.matrix[2][2] = _angleCos + (1.0f - _angleCos) * _axis.z * _axis.z;
        _result.matrix[2][3] = 0.0f;

        _result.matrix[3][0] = 0.0f;
        _result.matrix[3][1] = 0.0f;
        _result.matrix[3][2] = 0.0f;
        _result.matrix[3][3] = 1.0f;

        mat = mat * _result;
    }

    template<typename T>
    constexpr void Scale(Mat4x4<T>& mat, const Vec3<T>& vec) {
        Mat4x4<T> _result = Identity<T>();
        _result.matrix[0][0] = vec.x;
        _result.matrix[1][1] = vec.y;
        _result.matrix[2][2] = vec.z;
        mat = mat * _result;
    }

    template<typename T>
    constexpr Mat4x4<T> LookAt(const Vec3<T>& eye, const Vec3<T>& center, const Vec3<T>& up) {
        Vec3<T> _norm0 = Normalize(Vec3<T>(center.x - eye.x, center.y - eye.y, center.z - eye.z));
        Vec3<T> _norm1 = Normalize(CrossProduct(_norm0, up));
        Vec3<T> _norm2 = CrossProduct(_norm1, _norm0);

        Mat4x4<T> _result = Identity<T>();
        _result.matrix[0][0] = _norm1.x;
        _result.matrix[1][0] = _norm1.y;
        _result.matrix[2][0] = _norm1.z;
        _result.matrix[0][1] = _norm2.x;
        _result.matrix[1][1] = _norm2.y;
        _result.matrix[2][1] = _norm2.z;
        _result.matrix[0][2] = _norm0.x;
        _result.matrix[1][2] = _norm0.y;
        _result.matrix[2][2] = _norm0.z;
        _result.matrix[3][0] = -DotProduct(_norm1, eye);
        _result.matrix[3][1] = -DotProduct(_norm2, eye);
        _result.matrix[3][2] = -DotProduct(_norm0, eye);
        return _result;
    }

    template<typename T>
    constexpr Mat4x4<T> Inverse(const Mat4x4<T>& mat) {
        Mat4x4<T> _result;
        for(auto x = 0; x < 4; ++x) {
            for(auto y = 0; y < 4; ++y) {
                _result.matrix[x][y] = -mat.matrix[x][y];
            }
        }
        return _result;
    }
};
