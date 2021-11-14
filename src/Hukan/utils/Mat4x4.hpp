#pragma once

#include "../Hukan.hpp"

namespace hk {
    constexpr Int64_t pi = 3.14159265359;

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

        Mat4x4(T fov, T aspectRatio, T zNear, T zFar) { // REMEMBER FOV IN RADIANS
            Clear();
            T _halfFov = 1.0f / std::tan(1.0f * fov);
            matrix[0][0] = 1.0f / aspectRatio * _halfFov;
            matrix[1][1] = 1.0f / _halfFov;
            matrix[2][2] = zFar / (zFar - zNear);
            matrix[2][3] = 1.0f;
            matrix[3][2] = -(2.0f * zFar * zNear) / (zFar - zNear);
        }

        Mat4x4(T left, T right, T bottom, T top, T zNear, T zFar) {
            Clear();
            matrix[0][0] = 2.0f / (right - left);
            matrix[1][1] = 2.0f / (top - bottom);
            matrix[2][2] = -2.0f / (zFar - zNear);
            matrix[3][0] = -(right + left) / (right - left);
            matrix[3][1] = -(top + bottom) / (top - bottom);
            matrix[3][2] = -(zFar + zNear) / (zFar - zNear);
        }

        void Clear() {
            matrix = { std::array<T, 4>{ 0, 0, 0, 0 }, std::array<T, 4>{ 0, 0, 0, 0 }, std::array<T, 4>{ 0, 0, 0, 0 }, std::array<T, 4>{ 0, 0, 0, 0 } };
        }

        void Translate(const Vec3<T>& vec) {
            matrix[3][0] = matrix[0][0] * vec.x + matrix[1][0] * vec.y + matrix[2][0] * vec.z + matrix[3][0];
		    matrix[3][1] = matrix[0][1] * vec.x + matrix[1][1] * vec.y + matrix[2][1] * vec.z + matrix[3][1];
            matrix[3][2] = matrix[0][2] * vec.x + matrix[1][2] * vec.y + matrix[2][2] * vec.z + matrix[3][2];
		    matrix[3][3] = matrix[0][3] * vec.x + matrix[1][3] * vec.y + matrix[2][3] * vec.z + matrix[3][3];
        }

        void Scale(const Vec3<T>& vec) {
            Mat4x4<T> _result;
            _result.matrix[0][0] = vec.x;
            _result.matrix[1][1] = vec.y;
            _result.matrix[2][2] = vec.z;
            matrix = matrix * _result;
        }

        void SetMatrixAt(Int_t x, Int_t y, T data) {
            matrix[x][y] = data;
        }

        Mat4x4<T> operator*(const Mat4x4<T>& mat) {
            Mat4x4<T> _result;

            for(auto x = 0; x < 4; ++x) {
                for(auto x = 0; x < 4; ++x) {
                    for(auto x = 0; x < 4; ++x) {
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
    constexpr void Scale(Mat4x4<T>& mat, const Vec3<T>& vec) {
        Mat4x4<T> _result;
        mat.matrix[0][0] = vec.x;
        mat.matrix[1][1] = vec.y;
        mat.matrix[2][2] = vec.z;
        mat = mat * _result;
    }
};