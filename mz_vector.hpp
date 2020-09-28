#pragma once

#include "mz_common.hpp"

#define __d_p(x) std::fixed << std::setprecision(x)

namespace mz {

    typedef f32 default_value_t;

    template <typename value_t>
    struct vec2;
    template <typename value_t>
    struct vec3;
    template <typename value_t>
    struct vec4;

    typedef vec2<f32> fvec2;
    typedef fvec2     f32vec2;
    typedef vec2<f64> dvec2;
    typedef dvec2     f64vec2;

    typedef vec2<u8>  bvec2;
    typedef bvec2     u8vec2;
    typedef vec2<s8>  s8vec2;
    typedef vec2<u16> u16vec2;
    typedef vec2<s16> s16vec2;
    typedef vec2<u32> uvec2;
    typedef uvec2     u32vec2;
    typedef vec2<s32> ivec2;
    typedef ivec2     svec2;
    typedef svec2     s32vec2;
    typedef vec2<u64> u64vec2;
    typedef vec2<s64> lvec2;
    typedef lvec2     s64vec2;

    typedef vec3<f32> fvec3;
    typedef fvec3     f32vec3;
    typedef vec3<f64> dvec3;
    typedef dvec3     f64vec3;

    typedef vec3<u8>  bvec3;
    typedef bvec3     u8vec3;
    typedef vec3<s8>  s8vec3;
    typedef vec3<u16> u16vec3;
    typedef vec3<s16> s16vec3;
    typedef vec3<u32> uvec3;
    typedef uvec3     u32vec3;
    typedef vec3<s32> ivec3;
    typedef ivec3     svec3;
    typedef svec3     s32vec3;
    typedef vec3<u64> u64vec3;
    typedef vec3<s64> lvec3;
    typedef lvec3     s64vec3;

    typedef vec4<f32> fvec4;
    typedef fvec4     f32vec4;
    typedef vec4<f64> dvec4;
    typedef dvec4     f64vec4;

    typedef vec4<u8>  bvec4;
    typedef bvec4     u8vec4;
    typedef vec4<s8>  s8vec4;
    typedef vec4<u16> u16vec4;
    typedef vec4<s16> s16vec4;
    typedef vec4<u32> uvec4;
    typedef uvec4     u32vec4;
    typedef vec4<s32> ivec4;
    typedef ivec4     svec4;
    typedef svec4     s32vec4;
    typedef vec4<u64> u64vec4;
    typedef vec4<s64> lvec4;
    typedef lvec4     s64vec4;

    typedef fvec4     fcolor16;
    typedef fvec3     fcolor12;
    typedef dvec4     dcolor16;
    typedef dvec3     dcolor12;
    typedef bvec4     bcolor4;
    typedef bvec3     bcolor3;

    typedef fcolor16   color16;
    typedef fcolor16   color12;
    typedef color16    color;

    typedef bcolor4    color4;
    typedef bcolor3    color3;

    typedef ivec4     viewport;

    template <typename value_t>
    using rect = vec4<value_t>;

    typedef rect<f32> frect;
    typedef rect<s32> irect;

    template <typename value_t = default_value_t>
    struct vec2 {
        typedef value_t       value_type;
        typedef vec2<value_t> vec_type;

        static constexpr value_t zero = (value_t)0;

        constexpr mz_force_inline vec2() : x(zero), y(zero) {}
        template <typename value_x_t, typename value_y_t>
        constexpr mz_force_inline vec2(value_x_t x, value_y_t y) : x((value_t)x), y((value_t)y) {}
        template <typename rhs_value_t>
        constexpr mz_force_inline vec2(rhs_value_t ptr[2]) : ptr(ptr) {}
        constexpr mz_force_inline vec2(value_t scalar) : x(scalar), y(scalar) {}
        template <typename rhs_value_t>
        constexpr mz_force_inline vec2(const vec2<rhs_value_t>& v2) : x((value_t)v2.x), y((value_t)v2.y) {}
        template <typename rhs_value_t>
        constexpr mz_force_inline vec2(const vec3<rhs_value_t>& v3) : x((value_t)v3.x), y((value_t)v3.y) {}
        template <typename rhs_value_t>
        constexpr mz_force_inline vec2(const vec4<rhs_value_t>& v4) : x((value_t)v4.x), y((value_t)v4.y) {}

        union {
            value_t ptr[2];
            struct { value_t x, y; };
            struct { value_t r, g; };
            struct { value_t width, height; };
        };

        constexpr mz_force_inline value_t magnitude() const {
            return sqrt(x * x + y * y);
        }
        constexpr mz_force_inline vec_type normalize() const {
            value_t mag = magnitude();
            return vec_type(x / mag, y / mag);
        }
        constexpr mz_force_inline value_t distance(const vec_type& rhs) const {
            value_t a = x - rhs.x;
            value_t b = y - rhs.y;
            return sqrt(a * a + b * b);
        }
        constexpr mz_force_inline value_t dot(const vec_type& rhs) const {
            return x * rhs.x + y * rhs.y;
        }

        template <typename rhs_vec_t>
        constexpr mz_force_inline vec_type& add(const rhs_vec_t& rhs) {
            if constexpr (!std::is_same<rhs_vec_t, vec_type>()) {
                vec_type as_same_type = (vec_type)rhs;
                return add(as_same_type);
            } else {
                return *this;
            }
        }
        template <typename rhs_vec_t>
        constexpr mz_force_inline vec_type& subtract(const rhs_vec_t& rhs) {
            if constexpr (!std::is_same<rhs_vec_t, vec_type>()) {
                vec_type as_same_type = (vec_type)rhs;
                return subtract(as_same_type);
            } else {
                x -= rhs.x;
                y -= rhs.y;
                return *this;
            }
        }
        template <typename rhs_vec_t>
        constexpr mz_force_inline vec_type& multiply(const rhs_vec_t& rhs) {
            if constexpr (!std::is_same<rhs_vec_t, vec_type>()) {
                vec_type as_same_type = (vec_type)rhs;
                return multiply(as_same_type);
            } else {
                x *= rhs.x;
                y *= rhs.y;
                return *this;
            }
        }
        template <typename rhs_vec_t>
        constexpr mz_force_inline vec_type& divide(const rhs_vec_t& rhs) {
            if constexpr (!std::is_same<rhs_vec_t, vec_type>()) {
                vec_type as_same_type = (vec_type)rhs;
                return divide(as_same_type);
            } else {
                x /= rhs.x;
                y /= rhs.y;
                return *this;
            }
        }
        constexpr mz_force_inline vec_type& add(value_t rhs) {
            x += rhs;
            y += rhs;
            return *this;
        }
        constexpr mz_force_inline vec_type& subtract(value_t rhs) {
            x -= rhs;
            y -= rhs;
            return *this;
        }
        constexpr mz_force_inline vec_type& multiply(value_t rhs) {
            x *= rhs;
            y *= rhs;
            return *this;
        }
        constexpr mz_force_inline vec_type& divide(value_t rhs) {
            x /= rhs;
            y /= rhs;
            return *this;
        }

        constexpr mz_force_inline vec_type operator-() {
            x = -x;
            y = -y;
            return *this;
        }

        template <typename rhs_candidate_t>
        constexpr mz_force_inline friend vec_type operator+(vec_type lhs, const rhs_candidate_t& rhs) {
            return lhs.add(rhs);
        }
        template <typename rhs_candidate_t>
        constexpr mz_force_inline friend vec_type operator-(vec_type lhs, const rhs_candidate_t& rhs) {
            return lhs.subtract(rhs);
        }
        template <typename rhs_candidate_t>
        constexpr mz_force_inline friend vec_type operator*(vec_type lhs, const rhs_candidate_t& rhs) {
            return lhs.multiply(rhs);
        }
        template <typename rhs_candidate_t>
        constexpr mz_force_inline friend vec_type operator/(vec_type lhs, const rhs_candidate_t& rhs) {
            return lhs.divide(rhs);
        }

        template <typename rhs_value_t>
        constexpr mz_force_inline bool operator==(const vec2<rhs_value_t>& rhs) const {
            return x == rhs.x && y == rhs.y;
        }
        template <typename rhs_value_t>
        constexpr mz_force_inline bool operator!=(const vec2<rhs_value_t>& rhs) const {
            return !(*this == rhs);
        }

        template <typename rhs_candidate_t>
        constexpr mz_force_inline vec_type& operator+=(const rhs_candidate_t& rhs) {
            add(rhs);
            return *this;
        }
        template <typename rhs_candidate_t>
        constexpr mz_force_inline vec_type& operator-=(const rhs_candidate_t& rhs) {
            subtract(rhs);
            return *this;
        }
        template <typename rhs_candidate_t>
        constexpr mz_force_inline vec_type& operator*=(const rhs_candidate_t& rhs) {
            multiply(rhs);
            return *this;
        }
        template <typename rhs_candidate_t>
        constexpr mz_force_inline vec_type& operator/=(const rhs_candidate_t& rhs) {
            divide(rhs);
            return *this;
        }

        template <typename rhs_vec_t>
        constexpr mz_force_inline bool operator<(const rhs_vec_t& rhs) const {
            return magnitude() < rhs.magnitude();
        }
        template <typename rhs_vec_t>
        constexpr mz_force_inline bool operator<=(const rhs_vec_t& rhs) const {
            return magnitude() <= rhs.magnitude();
        }
        template <typename rhs_vec_t>
        constexpr mz_force_inline bool operator>(const rhs_vec_t& rhs) const {
            return magnitude() > rhs.magnitude();
        }
        template <typename rhs_vec_t>
        constexpr mz_force_inline bool operator>=(const rhs_vec_t& rhs) const {
            return magnitude() >= rhs.magnitude();
        }
    };

    template <typename value_t = default_value_t>
    struct vec3 {
        typedef value_t value_type;
        typedef vec3<value_t> vec_type;

        static constexpr value_t zero = (value_t)0;

        constexpr mz_force_inline vec3() : x(zero), y(zero) {}
        template <typename value_x_t, typename value_y_t, typename value_z_t>
        constexpr mz_force_inline vec3(value_x_t x, value_y_t y, value_z_t z) : x((value_t)x), y((value_t)y), z((value_t)z) {}
        template <typename rhs_value_t>
        constexpr mz_force_inline vec3(rhs_value_t ptr[3]) : ptr(ptr) {}
        constexpr mz_force_inline vec3(value_t scalar) : x(scalar), y(scalar), z(scalar) {}
        template <typename value_xy_t, typename value_z_t>
        constexpr mz_force_inline vec3(const vec2<value_xy_t>& xy, value_z_t z) : x((value_t)xy.x), y((value_t)xy.y), z((value_t)z) {}
        template <typename rhs_value_t>
        constexpr mz_force_inline vec3(const vec2<rhs_value_t>& v2) : x((value_t)v2.x), y((value_t)v2.y), z((value_t)zero) {}
        template <typename rhs_value_t>
        constexpr mz_force_inline vec3(const vec3<rhs_value_t>& v3) : x((value_t)v3.x), y((value_t)v3.y), z((value_t)v3.z) {}
        template <typename rhs_value_t>
        constexpr mz_force_inline vec3(const vec4<rhs_value_t>& v4) : x((value_t)v4.x), y((value_t)v4.y), z((value_t)v4.z) {}

        union {
            value_t ptr[3];
            struct { value_t x, y, z; };
            struct { value_t r, g, b; };
            struct { value_t width, height, depth; };
            vec2<value_t> v2;
        };

        template <typename other_value_t>
        inline operator vec2<other_value_t>& () {
            return v2;
        }

        constexpr mz_force_inline value_t magnitude() const {
            return sqrt(x * x + y * y + z * z);
        }
        constexpr mz_force_inline vec_type normalize() const {
            value_t mag = magnitude();
            return vec_type(x / mag, y / mag, z / mag);
        }
        constexpr mz_force_inline value_t distance(const vec_type& rhs) const {
            value_t a = x - rhs.x;
            value_t b = y - rhs.y;
            value_t c = z - rhs.z;
            return sqrt(a * a + b * b + c * c);
        }
        constexpr mz_force_inline value_t dot(const vec_type& rhs) const {
            return x * rhs.x + y * rhs.y + z * rhs.z;
        }

        constexpr mz_force_inline vec_type cross(const vec_type& other) const {
            return vec3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
        }

        template <typename rhs_vec_t>
        constexpr mz_force_inline vec_type& add(const rhs_vec_t& rhs) {
            if constexpr (!std::is_same<rhs_vec_t, vec_type>()) {
                vec_type as_same_type = (vec_type)rhs;
                return add(as_same_type);
            } else {
                x += rhs.x;
                y += rhs.y;
                z += rhs.z;
            }
            return *this;
        }
        template <typename rhs_vec_t>
        constexpr mz_force_inline vec_type& subtract(const rhs_vec_t& rhs) {
            if constexpr (!std::is_same<rhs_vec_t, vec_type>()) {
                vec_type as_same_type = (vec_type)rhs;
                return subtract(as_same_type);
            } else {
                x -= rhs.x;
                y -= rhs.y;
                z -= rhs.z;
                return *this;
            }
        }
        template <typename rhs_vec_t>
        constexpr mz_force_inline vec_type& multiply(const rhs_vec_t& rhs) {
            if constexpr (!std::is_same<rhs_vec_t, vec_type>()) {
                vec_type as_same_type = (vec_type)rhs;
                return multiply(as_same_type);
            } else {
                x *= rhs.x;
                y *= rhs.y;
                z *= rhs.z;
                return *this;
            }
        }
        template <typename rhs_vec_t>
        constexpr mz_force_inline vec_type& divide(const rhs_vec_t& rhs) {
            if constexpr (!std::is_same<rhs_vec_t, vec_type>()) {
                vec_type as_same_type = (vec_type)rhs;
                return divide(as_same_type);
            } else {
                x /= rhs.x;
                y /= rhs.y;
                z /= rhs.z;
                return *this;
            }
        }
        constexpr mz_force_inline vec_type& add(value_t rhs) {
            x += rhs;
            y += rhs;
            z += rhs;
            return *this;
        }
        constexpr mz_force_inline vec_type& subtract(value_t rhs) {
            x -= rhs;
            y -= rhs;
            z -= rhs;
            return *this;
        }
        constexpr mz_force_inline vec_type& multiply(value_t rhs) {
            x *= rhs;
            y *= rhs;
            z *= rhs;
            return *this;
        }
        constexpr mz_force_inline vec_type& divide(value_t rhs) {
            x /= rhs;
            y /= rhs;
            z /= rhs;
            return *this;
        }

        constexpr mz_force_inline vec_type operator-() {
            x = -x;
            y = -y;
            z = -z;
            return *this;
        }

        template <typename rhs_candidate_t>
        constexpr mz_force_inline friend vec_type operator+(vec_type lhs, const rhs_candidate_t& rhs) {
            return lhs.add(rhs);
        }
        template <typename rhs_candidate_t>
        constexpr mz_force_inline friend vec_type operator-(vec_type lhs, const rhs_candidate_t& rhs) {
            return lhs.subtract(rhs);
        }
        template <typename rhs_candidate_t>
        constexpr mz_force_inline friend vec_type operator*(vec_type lhs, const rhs_candidate_t& rhs) {
            return lhs.multiply(rhs);
        }
        template <typename rhs_candidate_t>
        constexpr mz_force_inline friend vec_type operator/(vec_type lhs, const rhs_candidate_t& rhs) {
            return lhs.divide(rhs);
        }

        template <typename rhs_value_t>
        constexpr mz_force_inline bool operator==(const vec3<rhs_value_t>& rhs) const {
            return x == rhs.x && y == rhs.y && z == rhs.z;
        }
        template <typename rhs_value_t>
        constexpr mz_force_inline bool operator!=(const vec3<rhs_value_t>& rhs) const {
            return !(*this == rhs);
        }

        template <typename rhs_candidate_t>
        constexpr mz_force_inline vec_type& operator+=(const rhs_candidate_t& rhs) {
            add(rhs);
            return *this;
        }
        template <typename rhs_candidate_t>
        constexpr mz_force_inline vec_type& operator-=(const rhs_candidate_t& rhs) {
            subtract(rhs);
            return *this;
        }
        template <typename rhs_candidate_t>
        constexpr mz_force_inline vec_type& operator*=(const rhs_candidate_t& rhs) {
            multiply(rhs);
            return *this;
        }
        template <typename rhs_candidate_t>
        constexpr mz_force_inline vec_type& operator/=(const rhs_candidate_t& rhs) {
            divide(rhs);
            return *this;
        }

        template <typename rhs_vec_t>
        constexpr mz_force_inline bool operator<(const rhs_vec_t& rhs) const {
            return magnitude() < rhs.magnitude();
        }
        template <typename rhs_vec_t>
        constexpr mz_force_inline bool operator<=(const rhs_vec_t& rhs) const {
            return magnitude() <= rhs.magnitude();
        }
        template <typename rhs_vec_t>
        constexpr mz_force_inline bool operator>(const rhs_vec_t& rhs) const {
            return magnitude() > rhs.magnitude();
        }
        template <typename rhs_vec_t>
        constexpr mz_force_inline bool operator>=(const rhs_vec_t& rhs) const {
            return magnitude() >= rhs.magnitude();
        }
    };

    template <typename value_t = default_value_t>
    struct vec4 {
        typedef value_t value_type;
        typedef vec4<value_t> vec_type;

        static constexpr value_t zero = (value_t)0;

        constexpr mz_force_inline vec4() : x(zero), y(zero), z(zero), w(zero) {}
        template <typename value_x_t, typename value_y_t, typename value_z_t, typename value_w_t>
        constexpr mz_force_inline vec4(value_x_t x, value_y_t y, value_z_t z, value_w_t w) : x((value_t)x), y((value_t)y), z((value_t)z), w((value_t)w) {}
        template <typename rhs_value_t>
        constexpr mz_force_inline vec4(rhs_value_t ptr[4]) : ptr(ptr) {}
        constexpr mz_force_inline vec4(value_t scalar) : x(scalar), y(scalar), z(scalar), w(scalar) {}
        template <typename value_xy_t, typename value_z_t, typename value_w_t>
        constexpr mz_force_inline vec4(const vec2<value_xy_t>& xy, value_z_t z, value_w_t w = (value_w_t)0) : x((value_t)xy.x), y((value_t)xy.y), z((value_t)z), w((value_t)w) {}
        template <typename value_xyz_t, typename value_w_t>
        constexpr mz_force_inline vec4(const vec3<value_xyz_t>& xyz, value_w_t w) : x((value_t)xyz.x), y((value_t)xyz.y), z((value_t)xyz.z), w((value_t)w) {}
        template <typename rhs_value_t>
        constexpr mz_force_inline vec4(const vec2<rhs_value_t>& v2) : x((value_t)v2.x), y((value_t)v2.y), z(zero), w(zero) {}
        template <typename rhs_value_t>
        constexpr mz_force_inline vec4(const vec3<rhs_value_t>& v3) : x((value_t)v3.x), y((value_t)v3.y), z((value_t)v3.z), w(zero) {}
        template <typename rhs_value_t>
        constexpr mz_force_inline vec4(const vec4<rhs_value_t>& v4) : x((value_t)v4.x), y((value_t)v4.y), z((value_t)v4.z), w((value_t)v4.w) {}

        union {
            value_t ptr[4];
            struct { value_t x, y, z, w; };
            struct { value_t r, g, b, a; };
            struct { value_t x_coord, y_coord, width, height; };
            vec2<value_t> v2;
            vec3<value_t> v3;
        };

        template <typename other_value_t>
        inline operator vec2<other_value_t>& () {
            return v2;
        }
        template <typename other_value_t>
        inline operator vec3<other_value_t>& () {
            return v3;
        }

        constexpr mz_force_inline value_t magnitude() const {
            return sqrt(x * x + y * y + z * z + w * w);
        }
        constexpr mz_force_inline vec_type normalize() const {
            value_t mag = magnitude();
            return vec_type(x / mag, y / mag, z / mag, w / mag);
        }
        constexpr mz_force_inline value_t distance(const vec_type& rhs) const {
            value_t a = x - rhs.x;
            value_t b = y - rhs.y;
            value_t c = z - rhs.z;
            value_t d = w - rhs.w;
            return sqrt(a * a + b * b + c * c + d * d);
        }
        constexpr mz_force_inline value_t dot(const vec_type& rhs) const {
            return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
        }

        template <typename rhs_vec_t>
        constexpr mz_force_inline vec_type& add(const rhs_vec_t& rhs) {
            if constexpr (!std::is_same<rhs_vec_t, vec_type>()) {
                vec_type as_same_type = (vec_type)rhs;
                return add(as_same_type);
            } else {
                x += rhs.x;
                y += rhs.y;
                z += rhs.z;
                w += rhs.w;
            }
            return *this;
        }
        template <typename rhs_vec_t>
        constexpr mz_force_inline vec_type& subtract(const rhs_vec_t& rhs) {
            if constexpr (!std::is_same<rhs_vec_t, vec_type>()) {
                vec_type as_same_type = (vec_type)rhs;
                return subtract(as_same_type);
            } else {
                x -= rhs.x;
                y -= rhs.y;
                z -= rhs.z;
                w -= rhs.w;
                return *this;
            }
        }
        template <typename rhs_vec_t>
        constexpr mz_force_inline vec_type& multiply(const rhs_vec_t& rhs) {
            if constexpr (!std::is_same<rhs_vec_t, vec_type>()) {
                vec_type as_same_type = (vec_type)rhs;
                return multiply(as_same_type);
            } else {
                x *= rhs.x;
                y *= rhs.y;
                z *= rhs.z;
                w *= rhs.w;
                return *this;
            }
        }
        template <typename rhs_vec_t>
        constexpr mz_force_inline vec_type& divide(const rhs_vec_t& rhs) {
            if constexpr (!std::is_same<rhs_vec_t, vec_type>()) {
                vec_type as_same_type = (vec_type)rhs;
                return divide(as_same_type);
            } else {
                x /= rhs.x;
                y /= rhs.y;
                z /= rhs.z;
                w /= rhs.w;
                return *this;
            }
        }
        constexpr mz_force_inline vec_type& add(value_t rhs) {
            x += rhs;
            y += rhs;
            z += rhs;
            w += rhs;
            return *this;
        }
        constexpr mz_force_inline vec_type& subtract(value_t rhs) {
            x -= rhs;
            y -= rhs;
            z -= rhs;
            w -= rhs;
            return *this;
        }
        constexpr mz_force_inline vec_type& multiply(value_t rhs) {
            x *= rhs;
            y *= rhs;
            z *= rhs;
            w *= rhs;
            return *this;
        }
        constexpr mz_force_inline vec_type& divide(value_t rhs) {
            x /= rhs;
            y /= rhs;
            z /= rhs;
            w /= rhs;
            return *this;
        }

        constexpr mz_force_inline vec_type operator-() {
            x = -x;
            y = -y;
            z = -z;
            w = -w;
            return *this;
        }

        template <typename rhs_candidate_t>
        constexpr mz_force_inline friend vec_type operator+(vec_type lhs, const rhs_candidate_t& rhs) {
            return lhs.add(rhs);
        }
        template <typename rhs_candidate_t>
        constexpr mz_force_inline friend vec_type operator-(vec_type lhs, const rhs_candidate_t& rhs) {
            return lhs.subtract(rhs);
        }
        template <typename rhs_candidate_t>
        constexpr mz_force_inline friend vec_type operator*(vec_type lhs, const rhs_candidate_t& rhs) {
            return lhs.multiply(rhs);
        }
        template <typename rhs_candidate_t>
        constexpr mz_force_inline friend vec_type operator/(vec_type lhs, const rhs_candidate_t& rhs) {
            return lhs.divide(rhs);
        }

        template <typename rhs_value_t>
        constexpr mz_force_inline bool operator==(const vec4<rhs_value_t>& rhs) const {
            return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
        }
        template <typename rhs_value_t>
        constexpr mz_force_inline bool operator!=(const vec4<rhs_value_t>& rhs) const {
            return !(*this == rhs);
        }

        template <typename rhs_candidate_t>
        constexpr mz_force_inline vec_type& operator+=(const rhs_candidate_t& rhs) {
            add(rhs);
            return *this;
        }
        template <typename rhs_candidate_t>
        constexpr mz_force_inline vec_type& operator-=(const rhs_candidate_t& rhs) {
            subtract(rhs);
            return *this;
        }
        template <typename rhs_candidate_t>
        constexpr mz_force_inline vec_type& operator*=(const rhs_candidate_t& rhs) {
            multiply(rhs);
            return *this;
        }
        template <typename rhs_candidate_t>
        constexpr mz_force_inline vec_type& operator/=(const rhs_candidate_t& rhs) {
            divide(rhs);
            return *this;
        }

        template <typename rhs_vec_t>
        constexpr mz_force_inline bool operator<(const rhs_vec_t& rhs) const {
            return magnitude() < rhs.magnitude();
        }
        template <typename rhs_vec_t>
        constexpr mz_force_inline bool operator<=(const rhs_vec_t& rhs) const {
            return magnitude() <= rhs.magnitude();
        }
        template <typename rhs_vec_t>
        constexpr mz_force_inline bool operator>(const rhs_vec_t& rhs) const {
            return magnitude() > rhs.magnitude();
        }
        template <typename rhs_vec_t>
        constexpr mz_force_inline bool operator>=(const rhs_vec_t& rhs) const {
            return magnitude() >= rhs.magnitude();
        }
    };
    constexpr color COLOR_WHITE       = color(1.f);
    constexpr color COLOR_TRANSPARENT = color(0.f);
    constexpr color COLOR_BLUE        = color(.1f, .1f, .8f, 1.f);
    constexpr color COLOR_DARKGREY    = color(.2f, .2f, .2f, 1.f);
    constexpr color COLOR_RED         = color(.8f, .1f, .1f, 1.f);

    template<typename TStream, typename value_t>
    inline TStream& operator<<(TStream& str, const vec2<value_t>& v) {
        return str 
               << "{ x: " << __d_p(5) << v.x 
               << ", y: " << __d_p(5) << v.y
               << " }";
    }
    template<typename TStream, typename value_t>
    inline TStream& operator<<(TStream& str, const vec3<value_t>& v) {
        return str 
               << "{ x: " << __d_p(5) << v.x 
               << ", y: " << __d_p(5) << v.y
               << ", z: " << __d_p(5) << v.z
               << " }";
    }
    template<typename TStream, typename value_t>
    inline TStream& operator<<(TStream& str, const vec4<value_t>& v) {
        return str 
               << "{ x: " << __d_p(5) << v.x 
               << ", y: " << __d_p(5) << v.y
               << ", z: " << __d_p(5) << v.z
               << ", w: " << __d_p(5) << v.w
               << " }";
    }
}