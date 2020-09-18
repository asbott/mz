#pragma once

#include <iomanip>
#include <stdint.h>

#include "mz_config.hpp"

namespace mz {
    typedef uint8_t  u8;
    typedef int8_t   s8;
    typedef uint16_t u16;
    typedef int16_t  s16;
    typedef uint32_t u32;
    typedef int32_t  s32;
    typedef uint64_t u64;
    typedef int64_t  s64;

    typedef float    f32;
    typedef double   f64;

    constexpr f64 PI = 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093844609550582231725359408128481;

    template <typename value_t>
    value_t to_radians(value_t deg) {
        return deg * (value_t)PI / (value_t)180;
    }
    template <typename value_t>
    value_t to_degrees(value_t rad) {
        return rad * (value_t)180 / PI;
    }
}
