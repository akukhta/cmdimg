#include <memory>
#include <vector>
#include <iostream>
#include "Dimentions.hpp"

import imageCompressor;
import ImageParser;
import FXTPrinter;

int main(int argc, char ** argv) 
{
    if (argc == 1)
    {
        // TODO: Add help command here...
        return 0;
    }

    std::string_view path = argv[1];
    
    auto dims = Dimentions::get();
    FXTPrinter printer{ dims };
    ImageParser parser;
    std::vector<std::vector<RGB>> pixels;

    try
    {
        pixels = parser.parseImage(path);
    }
    catch (std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
        return -1;
    }

    ImageCompressor compressor{ std::move(pixels) };
    auto compressedImage = compressor.compressBilinear(dims.first, dims.second);
    printer.print(compressedImage);
    return 0;
}
