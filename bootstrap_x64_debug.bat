cmake . -B .\bin\ -A x64 -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=C:/Users/kukht/vcpkg/scripts/buildsystems/vcpkg.cmake
mkdir bin
cd bin
cmake --build .