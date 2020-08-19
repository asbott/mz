#pragma once

#if !defined(mz_no_force_inline) && !defined(mz_force_inline)
    #ifdef _MSC_VER
        #define mz_force_inline __forceinline
    #elif defined(__GNUC__) || defined (__MINGW32__) || defined(__MINGW64__)
        #define mz_force_inline __attribute__((always_inline)) inline
    #elif defined(__clang__)
        /* Clang is honest boi and actually inlines the function if we say so */
        #define mz_force_inline inline
    #else
        #define mz_force_inline inline
        #warning mz_force_inline could not be defined for compiler. Performance impact is possible.    
    #endif
#endif

#ifndef mz_force_inline
    #define mz_force_inline inline
#endif