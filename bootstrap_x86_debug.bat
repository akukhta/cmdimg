mkdir bin
cmake . -B .\bin\ -A Win32 -DCMAKE_BUILD_TYPE=Debug
cd bin
REM cmake --build .