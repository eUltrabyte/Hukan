cmake_minimum_required(VERSION 3.17)
project(Hukan)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_BUILD_TYPE Release)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DHUKAN_DEBUG")

include_directories(${PROJECT_NAME} PRIVATE ../..)
include_directories(${PROJECT_NAME} PRIVATE Hukan)

find_package(Vulkan REQUIRED FATAL_ERROR)
if(Vulkan_FOUND)
    include_directories(${Vulkan_INCLUDE_DIRS})
endif(Vulkan_FOUND)

if(UNIX)
    find_package(X11 REQUIRED)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
endif(UNIX)

set(Hukan_SOURCE
    ../include/stb_image.hpp
    Hukan/core/Build.hpp
    Hukan/utils/Types.hpp
    Hukan/utils/Clock.hpp
    Hukan/utils/Clock.cpp
    Hukan/utils/Vec2.hpp
    Hukan/utils/Vec3.hpp
    Hukan/utils/Vec4.hpp
    Hukan/utils/Mat4x4.hpp
    Hukan/api/Platform.hpp
    Hukan/api/Platform.cpp
    Hukan/api/Terminal.hpp
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
    Hukan/core/PhysicalDevice.hpp
    Hukan/core/PhysicalDevice.cpp
    Hukan/core/Device.hpp
    Hukan/core/Device.cpp
    Hukan/core/Buffer.hpp
    Hukan/core/Buffer.cpp
    Hukan/graphics/Window/Window.hpp
    Hukan/graphics/Window/Window.cpp
    Hukan/graphics/Window/Posix/WindowPosix.hpp
    Hukan/graphics/Window/Posix/WindowPosix.cpp
    Hukan/graphics/Window/Win32/WindowWin32.hpp
    Hukan/graphics/Window/Win32/WindowWin32.cpp
    Hukan/graphics/Surface/Surface.hpp
    Hukan/graphics/Surface/Surface.cpp
    Hukan/graphics/Surface/Posix/SurfacePosix.hpp
    Hukan/graphics/Surface/Posix/SurfacePosix.cpp
    Hukan/graphics/Surface/Win32/SurfaceWin32.hpp
    Hukan/graphics/Surface/Win32/SurfaceWin32.cpp
    Hukan/core/Core.hpp
    Hukan/core/Core.cpp
    Hukan/Hukan.hpp
)

add_library(${PROJECT_NAME} STATIC ${Hukan_SOURCE})

target_precompile_headers(${PROJECT_NAME} PRIVATE Hukan/hkpch.hpp Hukan/hkpch.cpp)

if(Vulkan_FOUND)
    if(UNIX)
        target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan X11 Threads::Threads)
    else(UNIX)
        target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan)
    endif(UNIX)
endif(Vulkan_FOUND)
