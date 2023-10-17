#include <memory>
#include <vector>
#include <iostream>
#include "Dimentions.hpp"

import ArgsParser;
import MediaPreviewer;

int main(int argc, char** argv)
{
    ArgsParser args{ argc, argv };

    try
    {
        MediaPreviewer previewer(args);
        previewer.preview();
        return 0;
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return -1;
    }
}
