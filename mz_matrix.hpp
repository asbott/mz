#pragma once

#include <string.h>

#include "mz_common.hpp"

namespace mz {

    template <typename value_t>
    struct mat4 {
        typedef mat4<value_t> mat_type;
        typedef vec4<value_t> vec4_type;
        typedef vec3<value_t> vec3_type;

        union {
            value_t data[4 * 4];
            vec4_type rows[4];
            value_t ptr [4 * 4];
        };

        mz_force_inline mat4() {
            memset(data, 0, 4 * 4 * sizeof(value_t));
            rows[0].x = rows[1].y = rows[2].z = rows[3].w = (value_t)1;
        }

        mz_force_inline mat4(value_t diagonal) {
            memset(data, 0, 4 * 4 * sizeof(value_t));
            rows[0].x = rows[1].y = rows[2].z = rows[3].w = diagonal;
        }
        

        mz_force_inline mat4& multiply(const mat4& other) {
            vec4_type const dstc0 = { rows[0].x, rows[1].x, rows[2].x, rows[3].x };
            vec4_type const dstc1 = { rows[0].y, rows[1].y, rows[2].y, rows[3].y };
            vec4_type const dstc2 = { rows[0].z, rows[1].z, rows[2].z, rows[3].z };
            vec4_type const dstc3 = { rows[0].w, rows[1].w, rows[2].w, rows[3].w };

            vec4_type const srcc0 = { other.rows[0].x, other.rows[1].x, other.rows[2].x, other.rows[3].x };
            vec4_type const srcc1 = { other.rows[0].y, other.rows[1].y, other.rows[2].y, other.rows[3].y };
            vec4_type const srcc2 = { other.rows[0].z, other.rows[1].z, other.rows[2].z, other.rows[3].z };
            vec4_type const srcc3 = { other.rows[0].w, other.rows[1].w, other.rows[2].w, other.rows[3].w };

            vec4_type resc0 = dstc0 * srcc0.x + dstc1 * srcc0.y + dstc2 * srcc0.z + dstc3 * srcc0.w;
            vec4_type resc1 = dstc0 * srcc1.x + dstc1 * srcc1.y + dstc2 * srcc1.z + dstc3 * srcc1.w;
            vec4_type resc2 = dstc0 * srcc2.x + dstc1 * srcc2.y + dstc2 * srcc2.z + dstc3 * srcc2.w;
            vec4_type resc3 = dstc0 * srcc3.x + dstc1 * srcc3.y + dstc2 * srcc3.z + dstc3 * srcc3.w;

            rows[0] = { resc0.x, resc1.x, resc2.x, resc3.x };
            rows[1] = { resc0.y, resc1.y, resc2.y, resc3.y };
            rows[2] = { resc0.z, resc1.z, resc2.z, resc3.z };
            rows[3] = { resc0.w, resc1.w, resc2.w, resc3.w };

            return *this;
        }

        mz_force_inline vec3_type multiply(const vec3_type& vec) const {
            return multiply((vec4_type)vec);
        }

        mz_force_inline vec4_type multiply(const vec4_type& vec) const {
            vec3_type c1 = { rows[0].x, rows[1].x, rows[2].x };
            vec3_type c2 = { rows[0].y, rows[1].y, rows[2].y };
            vec3_type c3 = { rows[0].z, rows[1].z, rows[2].z };
            vec3_type c4 = { rows[0].w, rows[1].w, rows[2].w };

            vec4_type const mov0(vec.x);
            vec4_type const mov1(vec.y);
            vec4_type const mul0 = c1 * mov0;
            vec4_type const mul1 = c2 * mov1;
            vec4_type const add0 = mul0 + mul1;
            vec4_type const mov2(vec.z);
            vec4_type const mov3(vec.w);
            vec4_type const mul2 = c3 * mov2;
            vec4_type const mul3 = c4 * mov3;
            vec4_type const add1 = mul2 + mul3;
            vec4_type const add2 = add0 + add1;
            return add2;
        }

        mz_force_inline friend mat_type operator*(mat_type left, const mat_type& right) {
            return left.multiply(right);
        }

        mz_force_inline mat_type& operator*=(const mat_type& other) {
            return multiply(other);
        }

        mz_force_inline friend vec3_type operator*(const mat_type& left, const vec3_type& right) {
            return left.multiply(right);
        }

        mz_force_inline friend vec4_type operator*(const mat_type& left, const vec4_type& right) {
            return left.multiply(right);
        }

        mz_force_inline vec3_type get_translation() {
            vec3_type vec (
                rows[0].w,
                rows[1].w,
                rows[2].w
            );
            return vec;
        }

        mz_force_inline mat_type& translate(const vec3_type& amount) {
            
            vec3_type c1 = { rows[0].x, rows[1].x, rows[2].x };
            vec3_type c2 = { rows[0].y, rows[1].y, rows[2].y };
            vec3_type c3 = { rows[0].z, rows[1].z, rows[2].z };
            vec3_type c4 = { rows[0].w, rows[1].w, rows[2].w };

            c4 = c1 * amount.x
               + c2 * amount.y
               + c3 * amount.z
               + c4;
            
            rows[0].w = c4.x;
            rows[1].w = c4.y;
            rows[2].w = c4.z;

            return *this;
        }

        mz_force_inline mat_type& rotate(value_t angle, const vec3_type& axis) {
            mat_type rotation((value_t)1);

            value_t r = angle;
            value_t c = cos(r);
            value_t s = sin(r);
            value_t omc = 1.0f - c;

            value_t x = axis.x;
            value_t y = axis.y;
            value_t z = axis.z;

            rotation.data[0 + 0 * 4] = x * x * omc + c;
            rotation.data[0 + 1 * 4] = y * x * omc + z * s;
            rotation.data[0 + 2 * 4] = x * z * omc - y * s;

            rotation.data[1 + 0 * 4] = x * y * omc - z * s;
            rotation.data[1 + 1 * 4] = y * y * omc + c;
            rotation.data[1 + 2 * 4] = y * z * omc + x * s;

            rotation.data[2 + 0 * 4] = x * z * omc + y * s;
            rotation.data[2 + 1 * 4] = y * z * omc - x * s;
            rotation.data[2 + 2 * 4] = z * z * omc + c;

            this->multiply(rotation);

            return *this;
        }

        mz_force_inline mat_type& scale(const vec3_type& scale) {
            mat_type mat((value_t)1);

            mat.rows[0].x += scale.x;
            mat.rows[1].y += scale.y;
            mat.rows[2].z += scale.z;

            this->multiply(mat);

            return *this;
        }

        mz_force_inline mat_type& transpose() {
            rows[0] = vec4<value_t>(rows[0].x, rows[1].x, rows[2].x, rows[3].x);
            rows[1] = vec4<value_t>(rows[0].y, rows[1].y, rows[2].y, rows[3].y);
            rows[2] = vec4<value_t>(rows[0].z, rows[1].z, rows[2].z, rows[3].z);
            rows[3] = vec4<value_t>(rows[0].w, rows[1].w, rows[2].w, rows[3].w);

            return *this;
        }

        mz_force_inline mat_type& invert() {
            value_t temp[16];

            temp[0] = data[5] * data[10] * data[15] -
                data[5] * data[11] * data[14] -
                data[9] * data[6] * data[15] +
                data[9] * data[7] * data[14] +
                data[13] * data[6] * data[11] -
                data[13] * data[7] * data[10];

            temp[4] = -data[4] * data[10] * data[15] +
                data[4] * data[11] * data[14] +
                data[8] * data[6] * data[15] -
                data[8] * data[7] * data[14] -
                data[12] * data[6] * data[11] +
                data[12] * data[7] * data[10];

            temp[8] = data[4] * data[9] * data[15] -
                data[4] * data[11] * data[13] -
                data[8] * data[5] * data[15] +
                data[8] * data[7] * data[13] +
                data[12] * data[5] * data[11] -
                data[12] * data[7] * data[9];

            temp[12] = -data[4] * data[9] * data[14] +
                data[4] * data[10] * data[13] +
                data[8] * data[5] * data[14] -
                data[8] * data[6] * data[13] -
                data[12] * data[5] * data[10] +
                data[12] * data[6] * data[9];

            temp[1] = -data[1] * data[10] * data[15] +
                data[1] * data[11] * data[14] +
                data[9] * data[2] * data[15] -
                data[9] * data[3] * data[14] -
                data[13] * data[2] * data[11] +
                data[13] * data[3] * data[10];

            temp[5] = data[0] * data[10] * data[15] -
                data[0] * data[11] * data[14] -
                data[8] * data[2] * data[15] +
                data[8] * data[3] * data[14] +
                data[12] * data[2] * data[11] -
                data[12] * data[3] * data[10];

            temp[9] = -data[0] * data[9] * data[15] +
                data[0] * data[11] * data[13] +
                data[8] * data[1] * data[15] -
                data[8] * data[3] * data[13] -
                data[12] * data[1] * data[11] +
                data[12] * data[3] * data[9];

            temp[13] = data[0] * data[9] * data[14] -
                data[0] * data[10] * data[13] -
                data[8] * data[1] * data[14] +
                data[8] * data[2] * data[13] +
                data[12] * data[1] * data[10] -
                data[12] * data[2] * data[9];

            temp[2] = data[1] * data[6] * data[15] -
                data[1] * data[7] * data[14] -
                data[5] * data[2] * data[15] +
                data[5] * data[3] * data[14] +
                data[13] * data[2] * data[7] -
                data[13] * data[3] * data[6];

            temp[6] = -data[0] * data[6] * data[15] +
                data[0] * data[7] * data[14] +
                data[4] * data[2] * data[15] -
                data[4] * data[3] * data[14] -
                data[12] * data[2] * data[7] +
                data[12] * data[3] * data[6];

            temp[10] = data[0] * data[5] * data[15] -
                data[0] * data[7] * data[13] -
                data[4] * data[1] * data[15] +
                data[4] * data[3] * data[13] +
                data[12] * data[1] * data[7] -
                data[12] * data[3] * data[5];

            temp[14] = -data[0] * data[5] * data[14] +
                data[0] * data[6] * data[13] +
                data[4] * data[1] * data[14] -
                data[4] * data[2] * data[13] -
                data[12] * data[1] * data[6] +
                data[12] * data[2] * data[5];

            temp[3] = -data[1] * data[6] * data[11] +
                data[1] * data[7] * data[10] +
                data[5] * data[2] * data[11] -
                data[5] * data[3] * data[10] -
                data[9] * data[2] * data[7] +
                data[9] * data[3] * data[6];

            temp[7] = data[0] * data[6] * data[11] -
                data[0] * data[7] * data[10] -
                data[4] * data[2] * data[11] +
                data[4] * data[3] * data[10] +
                data[8] * data[2] * data[7] -
                data[8] * data[3] * data[6];

            temp[11] = -data[0] * data[5] * data[11] +
                data[0] * data[7] * data[9] +
                data[4] * data[1] * data[11] -
                data[4] * data[3] * data[9] -
                data[8] * data[1] * data[7] +
                data[8] * data[3] * data[5];

            temp[15] = data[0] * data[5] * data[10] -
                data[0] * data[6] * data[9] -
                data[4] * data[1] * data[10] +
                data[4] * data[2] * data[9] +
                data[8] * data[1] * data[6] -
                data[8] * data[2] * data[5];

            value_t determinant = data[0] * temp[0] + data[1] * temp[4] + data[2] * temp[8] + data[3] * temp[12];
            determinant = 1.0f / determinant;

            for (u8 i = 0; i < 4 * 4; i++)
                data[i] = temp[i] * determinant;

            return *this;
        }
    };

    namespace transformation {
        template <typename value_t>
        mat4<value_t> translation(vec3<value_t> value) {
            mat4<value_t> mat(1.f);
            mat.translate(value);
            return mat;
        }

        template <typename value_t>
        mat4<value_t> rotation(value_t angle, vec3<value_t> axis) {
            mat4<value_t> mat(1.f);
            mat.rotate(angle, axis);
            return mat;
        }

        template <typename value_t>
        mat4<value_t> scale(vec3<value_t> value) {
            mat4<value_t> mat(1.f);
            mat.rows[0].x = value.x;
            mat.rows[1].y = value.y;
            mat.rows[2].z = value.z;
            return mat;
        }
    }

    namespace projection {

        template <typename value_t>
        mat4<value_t> ortho(value_t left, value_t right, value_t bottom, value_t top, value_t near_, value_t far_) {
            mat4 result(1.0f);

            result.data[0 + 0 * 4] = 2.0f / (right - left);

            result.data[1 + 1 * 4] = 2.0f / (top - bottom);

            result.data[2 + 2 * 4] = 2.0f / (near_ - far_);

            result.data[3 + 0 * 4] = (left + right) / (left - right);
            result.data[3 + 1 * 4] = (bottom + top) / (bottom - top);
            result.data[3 + 2 * 4] = (far_ + near_) / (far_ - near_);

            return result;
        }

        template <typename value_t>
        mat4<value_t> perspective(value_t fov, f32 aspectRatio, value_t near_, value_t far_) {
            mat4<value_t> result((value_t)1);

            value_t q = (value_t)(1.0f / tan(0.5f * fov));
            value_t a = (value_t)((f32)q / aspectRatio);

            value_t b = (value_t)((near_+ far_) / (near_- far_));
            value_t c = (value_t)((2.0f * near_* far_) / (near_- far_));

            result.data[0 + 0 * 4] = a;
            result.data[1 + 1 * 4] = q;
            result.data[2 + 2 * 4] = b;
            result.data[2 + 3 * 4] = -1.0f;
            result.data[3 + 2 * 4] = c;

            return result;
        }

        template <typename value_t>
        mat4<value_t> look_at(const vec3<value_t>& camera, const vec3<value_t>& object, const vec3<value_t>& up) {
            mat4<value_t> result = mat4<value_t>((value_t)0);
            vec3<value_t> f = (object - camera).normalize();
            vec3<value_t> s = f.cross(up.normalize());
            vec3<value_t> u = s.cross(f);

            result.data[0 + 0 * 4] = s.x;
            result.data[0 + 1 * 4] = s.y;
            result.data[0 + 2 * 4] = s.z;

            result.data[1 + 0 * 4] = u.x;
            result.data[1 + 1 * 4] = u.y;
            result.data[1 + 2 * 4] = u.z;

            result.data[2 + 0 * 4] = -f.x;
            result.data[2 + 1 * 4] = -f.y;
            result.data[2 + 2 * 4] = -f.z;

            return result * mat4<value_t>((value_t)1.f).translate(vec3<value_t>(-camera.x, -camera.y, -camera.z));
        }
    }

    template<typename TStream, typename value_t>
    inline TStream& operator<<(TStream& str, const mat4<value_t>& m) {
        return str << "mat4:\n"
               << m.rows[0] << "\n"
               << m.rows[1] << "\n"
               << m.rows[2] << "\n"
               << m.rows[3];
    }

    typedef mat4<f32> fmat4;
    typedef mat4<f64> dmat4;
    typedef mat4<s32> imat4;
}