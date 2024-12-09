set(SPDLOG_MASTER_PROJECT OFF)
add_subdirectory(spdlog)

set(GLFW_LIBRARY_TYPE "STATIC")
option(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)
add_subdirectory(glfw)