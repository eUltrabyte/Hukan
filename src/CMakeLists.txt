cmake_minimum_required(VERSION 3.17)
project(Hukan)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(VCPKG_TARGET_TRIPLET x64-windows)

if(CMAKE_BUILD_TYPE EQUAL "Debug")
    add_definitions(-DHUKAN_DEBUG)
endif(CMAKE_BUILD_TYPE EQUAL "Debug")

include_directories(${PROJECT_NAME} PRIVATE ../..)
include_directories(${PROJECT_NAME} PRIVATE Hukan)

find_package(Vulkan REQUIRED FATAL_ERROR)
if(Vulkan_FOUND)
    include_directories(${Vulkan_INCLUDE_DIRS})
endif(Vulkan_FOUND)

find_package(GLFW3 REQUIRED FATAL_ERROR)
if(GLFW3_FOUND)
    include_directories(${GLFW3_INCLUDE_DIRS})
endif(GLFW3_FOUND)

find_package(glm REQUIRED FATAL_ERROR)
if(glm_FOUND)
    include_directories(${glm_INCLUDE_DIRS})
endif(glm_FOUND)

set(Hukan_SOURCE
    Hukan/core/Build.hpp
    Hukan/utils/Types.hpp
    Hukan/utils/Clock.hpp
    Hukan/utils/Clock.cpp
    Hukan/api/Platform.hpp
    Hukan/api/Posix/PlatformPosix.cpp
    Hukan/api/Win32/PlatformWin32.cpp
    Hukan/api/Terminal.hpp
    Hukan/api/Posix/TerminalPosix.cpp
    Hukan/api/Win32/TerminalWin32.cpp
    Hukan/api/Logger.hpp
    Hukan/api/Logger.cpp
    Hukan/core/Assert.hpp
    Hukan/core/Assert.cpp
    Hukan/core/Instance.hpp
    Hukan/core/Instance.cpp
    Hukan/Hukan.hpp
    Hukan/Hukan.cpp
)

add_library(${PROJECT_NAME} STATIC ${Hukan_SOURCE})

target_precompile_headers(${PROJECT_NAME} PRIVATE Hukan/hkpch.hpp Hukan/hkpch.cpp)

if(Vulkan_FOUND AND GLFW3_FOUND AND glm_FOUND)
    target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan ${Vulkan_LIBRARIES} ${GLFW3_LIBRARIES} ${glm_LIBRARIES})
endif(Vulkan_FOUND AND GLFW3_FOUND AND glm_FOUND)