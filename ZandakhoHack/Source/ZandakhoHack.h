#pragma once

#ifdef ZH_BUILD_DLL
    #define ZH_API __declspec(dllexport)
#else
    #define ZH_API __declspec(dllimport)
#endif

extern "C" ZH_API bool InitializeHack();
extern "C" ZH_API void ShutdownHack();
