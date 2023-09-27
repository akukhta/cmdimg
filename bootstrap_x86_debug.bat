mkdir bin
conan install . --output-folder=bin --build=missing -pr .\x86_debug_profile.txt
cmake . -B .\bin\  --preset conan-default -A Win32 -DCMAKE_BUILD_TYPE=Debug