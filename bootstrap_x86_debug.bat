mkdir bin
cmake . -B .\bin\ -A Win32 -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake
cd bin
cmake --build .
