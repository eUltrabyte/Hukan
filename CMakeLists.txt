cmake_minimum_required(VERSION 3.17)
project(Hukan-Core)

include_directories(../..)
include_directories(src)
include_directories(src/Hukan)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

if(WIN32)
    set(GLSL_VALIDATOR "$ENV{VULKAN_SDK}/Bin/glslangValidator.exe")
else(WIN32)
    set(GLSL_VALIDATOR "$ENV{VULKAN_SDK}/bin/glslangValidator")
endif(WIN32)

file(GLOB_RECURSE GLSL_SOURCE_FILES
    "res/*.frag"
    "res/*.vert"
)

foreach(GLSL ${GLSL_SOURCE_FILES})
    get_filename_component(FILE_NAME ${GLSL} NAME)
    set(SPIRV "${PROJECT_BINARY_DIR}/${FILE_NAME}.spv")
    add_custom_command(OUTPUT ${SPIRV} COMMAND ${GLSL_VALIDATOR} -V ${GLSL} -o ${SPIRV} DEPENDS ${GLSL})
    list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach(GLSL)

add_custom_target(Hukan-Shaders DEPENDS ${SPIRV_BINARY_FILES})

add_subdirectory(src)

add_executable(Hukan-Example
    examples/Example.cpp
)

add_dependencies(Hukan-Example Hukan-Shaders)

target_link_libraries(Hukan-Example Hukan)

file(COPY res/ DESTINATION res/)
