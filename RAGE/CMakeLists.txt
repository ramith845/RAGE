set(RAGE_ROOT_PATH "src/Rage")
set(RAGE_EVENTS_PATH "src/Rage/Events")

add_library(Rage SHARED 
			"${RAGE_ROOT_PATH}/Application.cpp" 
			"${RAGE_ROOT_PATH}/Application.h" 
			"${RAGE_ROOT_PATH}/Log.cpp" 
			"${RAGE_ROOT_PATH}/Log.h"
			"${RAGE_ROOT_PATH}/Core.h"
			"${RAGE_ROOT_PATH}/EntryPoint.h"

			"${RAGE_EVENTS_PATH}/Event.h"
			"${RAGE_EVENTS_PATH}/KeyEvent.h"
			"${RAGE_EVENTS_PATH}/MouseEvent.h"
			"${RAGE_EVENTS_PATH}/ApplicationEvent.h"
			"src/Rage.h"
			"src/rgpch.h"
			"src/rgpch.cpp"
			)



target_compile_definitions(Rage PRIVATE RG_PLATFORM_WINDOWS RG_BUILD_DLL)
target_link_libraries(Rage PUBLIC rage_compiler_flags spdlog_header_only)
target_include_directories(Rage INTERFACE 
						   "${CMAKE_CURRENT_SOURCE_DIR}/src" 
						   "${CMAKE_CURRENT_SOURCE_DIR}/src/Rage/Events"
						   )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/Rage/Events)


if(MSVC)
	set_source_files_properties(src/rgpch.cpp PROPERTIES COMPILE_FLAGS "/Ycrgpch.h")
	set_target_properties(Rage PROPERTIES COMPILE_FLAGS "/Yurgpch.h")
endif()

add_subdirectory(src)
add_subdirectory("vendor/spdlog")

add_custom_command(TARGET Rage POST_BUILD 
				   COMMAND ${CMAKE_COMMAND} -E copy 
				   $<TARGET_FILE:Rage> "${CMAKE_BINARY_DIR}/bin/Sage-${CMAKE_HOST_SYSTEM_PROCESSOR}/$<CONFIG>"
				  )