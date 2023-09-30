mkdir bin
conan install . --output-folder=bin --build=missing -pr .\x64_debug_profile.txt
cmake . -B .\bin\  --preset conan-default -A x64 -DCMAKE_BUILD_TYPE=Debug