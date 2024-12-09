add_subdirectory(src)
add_subdirectory(vendor)

set(RAGE_ROOT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src/Rage")
set(RAGE_PLATFORM_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src/Platform")
set(RAGE_WINPLAT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/Windows")
set(RAGE_EVENTS_PATH "${RAGE_ROOT_PATH}/Events")
set(GLFW_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw/include")

add_library(Rage SHARED 
			"${RAGE_ROOT_PATH}/Application.cpp" 
			"${RAGE_ROOT_PATH}/Application.h" 
			"${RAGE_ROOT_PATH}/Log.cpp" 
			"${RAGE_ROOT_PATH}/Log.h"
			"${RAGE_ROOT_PATH}/Core.h"
			"${RAGE_ROOT_PATH}/EntryPoint.h"
			"${RAGE_ROOT_PATH}/Window.h"

			"${RAGE_WINPLAT_PATH}/WindowsWindow.cpp"
			"${RAGE_WINPLAT_PATH}/WindowsWindow.h"

			"${RAGE_EVENTS_PATH}/Event.h"
			"${RAGE_EVENTS_PATH}/KeyEvent.h"
			"${RAGE_EVENTS_PATH}/MouseEvent.h"
			"${RAGE_EVENTS_PATH}/ApplicationEvent.h"
			"src/Rage.h"
			"src/rgpch.h"
			"src/rgpch.cpp"
)

source_group(src FILES "src/Rage.h"
					   "src/rgpch.h"
					   "src/rgpch.cpp"
)
source_group(src/Rage FILES "${RAGE_ROOT_PATH}/Application.cpp" 
							"${RAGE_ROOT_PATH}/Application.h" 
							"${RAGE_ROOT_PATH}/Log.cpp" 
							"${RAGE_ROOT_PATH}/Log.h"
							"${RAGE_ROOT_PATH}/Core.h"
							"${RAGE_ROOT_PATH}/EntryPoint.h"
							"${RAGE_ROOT_PATH}/Window.h"
)
source_group(src/Rage/Events FILES "${RAGE_EVENTS_PATH}/Event.h"
								   "${RAGE_EVENTS_PATH}/KeyEvent.h"
								   "${RAGE_EVENTS_PATH}/MouseEvent.h"
								   "${RAGE_EVENTS_PATH}/ApplicationEvent.h"
)
source_group(src/Platform/Windows FILES "${RAGE_WINPLAT_PATH}/WindowsWindow.cpp" 
										"${RAGE_WINPLAT_PATH}/WindowsWindow.h"
)

target_compile_definitions(Rage PRIVATE RG_PLATFORM_WINDOWS RG_BUILD_DLL)
target_link_libraries(Rage PUBLIC rage_compiler_flags spdlog_header_only PRIVATE glfw opengl32)
target_include_directories(Rage PUBLIC 
								${CMAKE_CURRENT_SOURCE_DIR}/src
								${CMAKE_CURRENT_SOURCE_DIR}/src/Rage
								#${RAGE_WINPLAT_PATH}
								${RAGE_PLATFORM_PATH}
								PRIVATE
								${GLFW_INCLUDE_PATH}
						   )


if(MSVC)
	set_source_files_properties(src/rgpch.cpp PROPERTIES COMPILE_FLAGS "/Ycrgpch.h")
	set_target_properties(Rage PROPERTIES COMPILE_FLAGS "/Yurgpch.h")
endif()



# Post Rage build dll copy paste command
add_custom_command(TARGET Rage POST_BUILD 
				   COMMAND ${CMAKE_COMMAND} -E copy 
				   $<TARGET_FILE:Rage> "${CMAKE_BINARY_DIR}/bin/Sage-${CMAKE_HOST_SYSTEM_PROCESSOR}/$<CONFIG>/"
				  )