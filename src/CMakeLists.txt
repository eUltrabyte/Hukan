cmake_minimum_required(VERSION 3.17)
project(Hukan)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

if(CMAKE_BUILD_TYPE EQUAL "Debug")
    add_definitions(-DHUKAN_DEBUG)
endif(CMAKE_BUILD_TYPE EQUAL "Debug")

include_directories(${PROJECT_NAME} PRIVATE ../..)
include_directories(${PROJECT_NAME} PRIVATE Hukan)

find_package(Vulkan REQUIRED FATAL_ERROR)
if(Vulkan_FOUND)
    include_directories(${Vulkan_INCLUDE_DIRS})
endif(Vulkan_FOUND)

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
    Hukan/core/Messenger.hpp
    Hukan/core/Messenger.cpp
    Hukan/core/Layer.hpp
    Hukan/core/Layer.cpp
    Hukan/core/Extension.hpp
    Hukan/core/Extension.cpp
    Hukan/graphics/Window/Win32/WindowWin32.hpp
    Hukan/graphics/Window/Win32/WindowWin32.cpp
    Hukan/Hukan.hpp
    Hukan/Hukan.cpp
)

add_library(${PROJECT_NAME} STATIC ${Hukan_SOURCE})

target_precompile_headers(${PROJECT_NAME} PRIVATE Hukan/hkpch.hpp Hukan/hkpch.cpp)

if(Vulkan_FOUND)
    target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan ${Vulkan_LIBRARIES})
endif(Vulkan_FOUND)