# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()
if(CMAKE_GENERATOR MATCHES "Visual Studio")
	set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Dist")
endif()

set(config "${CMAKE_BUILD_TYPE}")
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")


project (Rage VERSION 1.0.0 LANGUAGES C CXX)

add_library(rage_compiler_flags INTERFACE)
target_compile_features(rage_compiler_flags INTERFACE cxx_std_20)
target_compile_definitions(rage_compiler_flags INTERFACE "WINDOWS_PLATFORM")
target_compile_options(rage_compiler_flags INTERFACE 
						"$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall,-Wextra,-Wshadow,-Wformat=2,-Wunused>>"
						"$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
					   )

# Include sub-projects.
add_subdirectory (SAGE)
add_subdirectory (RAGE)


# Set output directories for SAGE
set(SAGE_RUNTIME_OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin/Sage-${CMAKE_HOST_SYSTEM_PROCESSOR}")
# Apply output directory settings for all targets in subprojects
set_target_properties(Sage PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${SAGE_RUNTIME_OUTPUT_DIR})

# Set output directories for RAGE
set(RAGE_RUNTIME_OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin/Rage-${CMAKE_HOST_SYSTEM_PROCESSOR}")
# Apply output directory settings for all targets in subprojects
set_target_properties(Rage PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${RAGE_RUNTIME_OUTPUT_DIR})

