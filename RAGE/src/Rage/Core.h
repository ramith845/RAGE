#pragma once

#ifdef RG_PLATFORM_WINDOWS
  #ifdef RG_BUILD_DLL
    #define RAGE_API __declspec(dllexport)
  #else
    #define RAGE_API __declspec(dllimport)
  #endif // RG_BUILD_DLL
#else
  #error Rage support on non-windows platform is progress
#endif // RG_WINDOWS_PLATFORM