cmake_minimum_required(VERSION 3.17)
project(Hukan)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)

include_directories(${PROJECT_NAME} PRIVATE ../..)
include_directories(${PROJECT_NAME} PRIVATE Hukan)

find_package(Vulkan REQUIRED)
if(Vulkan_FOUND)
    include_directories(${Vulkan_INCLUDE_DIRS})
endif(Vulkan_FOUND)

find_package(GLFW3 REQUIRED)
if(GLFW3_FOUND)
    include_directories(${GLFW3_INCLUDE_DIRS})
endif(GLFW3_FOUND)

find_package(glm REQUIRED)
if(glm_FOUND)
    include_directories(${glm_INCLUDE_DIRS})
endif(glm_FOUND)

set(Hukan_SOURCE
    Hukan/utils/Types.hpp
    Hukan/utils/Clock.hpp
    Hukan/utils/Clock.cpp
    Hukan/api/Build.hpp
    Hukan/api/Platform.hpp
    Hukan/api/Posix/PlatformPosix.cpp
    Hukan/api/Win32/PlatformWin32.cpp
    Hukan/api/Terminal.hpp
    Hukan/api/Posix/TerminalPosix.cpp
    Hukan/api/Win32/TerminalWin32.cpp
    Hukan/api/Logger.hpp
    Hukan/api/Logger.cpp
    Hukan/Hukan.hpp
    Hukan/Hukan.cpp
)

add_library(${PROJECT_NAME} STATIC ${Hukan_SOURCE})

target_precompile_headers(${PROJECT_NAME} PRIVATE Hukan/hkpch.hpp Hukan/hkpch.cpp)

if(Vulkan_FOUND AND GLFW3_FOUND AND glm_FOUND)
    target_link_libraries(${PROJECT_NAME} ${Vulkan_LIBRARIES} ${GLFW3_LIBRARIES} ${glm_LIBRARIES})
endif(Vulkan_FOUND AND GLFW3_FOUND AND glm_FOUND)