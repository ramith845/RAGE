add_executable(Sage "src/SageApp.cpp")

target_link_libraries(Sage PUBLIC rage_compiler_flags Rage spdlog_header_only)
target_compile_definitions(Sage PRIVATE RG_PLATFORM_WINDOWS)