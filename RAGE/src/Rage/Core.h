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


#ifdef _DEBUG
#define RG_CORE_ASSERT(x, ...) if(!(x)) {RG_CORE_ERROR("Assertion failed {0}", __VA_ARGS__); __debugbreak();}
#define RG_CLIENT_ASSERT(x, ...) if(!(x)) {RG_CORE_ERROR("Assertion failed {0}", __VA_ARGS__); __debugbreak();}
#else
#define RG_CORE_ASSERT
#define RG_CLIENT_ASSERT
#endif // _DEBUG


#define BIT(number) (1 << number)