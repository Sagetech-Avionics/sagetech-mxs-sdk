cmake_minimum_required(VERSION 3.9)

project(sagetech-sdk-public)
enable_language(C CXX ASM)


# export the library target through a variable to CMakeLists.txt files in subdirectories.
# update the dependent sources.
add_library(${PROJECT_NAME}
    ""
)

if (LINKER_SCRIPT)
	# if linker script is defined, make the target to depends on it,
	# so the target will be rebuilt when linker script was changed.
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT})
endif()

# Add external explicit libraries. Such as 'm' for libm (math.h).
target_link_libraries(${PROJECT_NAME} PRIVATE m)


# export the name of library target via a variable to CMakeLists.txt files in subdirectories.
set(CURRENT_LIB_NAME ${PROJECT_NAME})
# load and run the CMake code from subdirectories for current target.
include(util/CMakeLists.txt)
include(sdk/CMakeLists.txt)
