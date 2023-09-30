# cmdimg
CLI Utility to preview files directly from the command line

# Dependencies
- OpenCV
  - OpenCV is being used to actually read and decompress an image. Could be used more lightweight library/own implementation
- FTXUI 
  - A great library to create fancy GUI for a command line application. [The library repository](https://github.com/ArthurSonzogni/FTXUI)

# Building
```
git clone https://github.com/akukhta/cmdimg
cd cmdimg
bootstrap_x86_debug.bat
```
# Usage
```
cmdimg scream.jpg
```
![Screenshot 2023-09-30 230505](https://github.com/akukhta/cmdimg/assets/45069472/61ae4ef0-d907-44fe-8713-c0c542ffe77f)

> [!WARNING]
> To actually preview the image, the terminal should support true color!
