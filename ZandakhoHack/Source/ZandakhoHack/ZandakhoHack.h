#pragma once

#ifdef ZH_BUILD_DLL
    #define ZH_API __declspec(dllexport)
#else
    #define ZH_API __declspec(dllimport)
#endif
