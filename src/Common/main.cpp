#include <memory>
#include <vector>
#include <iostream>
#include "Dimentions.hpp"

import imageCompressor;
import ImageParser;
import FXTPrinter;
import ArgsParser;

int main(int argc, char** argv)
{
    ArgsParser args{ argc, argv };

    auto dims = Dimentions::get(args.border());
    FXTPrinter printer{ dims };
    ImageParser parser;
    std::vector<std::vector<RGB>> pixels;

    try
    {
        pixels = parser.parseImage(args.fileName());
    }
    catch (std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
        return -1;
    }

    ImageCompressor compressor{ std::move(pixels) };
    auto compressedImage = compressor.compressBilinear(dims.first, dims.second);
    printer.print(compressedImage, args.border());
    return 0;
}
