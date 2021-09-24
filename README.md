### cmake with vcpkg
##### for you: cmake -G "your compiler" .. -DVCPKG_TARGET_TRIPLET=<your triplet> -DCMAKE_TOOLCHAIN_FILE=your vcpkg path
##### for me: cmake -G "NMake Makefiles" .. -DVCPKG_TARGET_TRIPLET=x64-windows -DCMAKE_TOOLCHAIN_FILE=C:\vcpkg\scripts\buildsystems\vcpkg.cmake