# cmdimg
CLI Utility to preview media files directly from the command line

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

![demo](https://github.com/akukhta/cmdimg/assets/45069472/2c5ceb06-97a3-4dc5-af93-a163a9446af4)

> [!WARNING]
> To actually preview the image, the terminal should support true color!

> [!NOTE]
> Currently the tool supports only following formats: BMP, JPG, JP2, PNG, WEBP, AVIF, PBM, PFM, SR, TIFF, EXR, HDR, PIC, AVI
