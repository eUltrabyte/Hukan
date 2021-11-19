#pragma once

#include "Core.hpp"

#define HUKAN_STATIC_LIBRARY
#if defined(HUKAN_STATIC_LIBRARY)
    #define HK_API
#else
    #if defined(HUKAN_DLL_BUILD)
        #if defined(_MSC_VER)
            #define HK_API __declspec(dllexport)
        #else
            #define HK_API __attribute__((visibility("default")))
        #endif
    #else
        #if defined(_MSC_VER)
            #define HK_API __declspec(dllimport)
        #else
            #define HK_API __attribute__((visibility("hidden")))
        #endif
    #endif
#endif