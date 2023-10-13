#include <memory>
#include <vector>
#include <iostream>
#include "Dimentions.hpp"

import ArgsParser;
import MediaPreviewer;

int main(int argc, char** argv)
{
    ArgsParser args{ argc, argv };
    MediaPreviewer previewer(args);
    
    previewer.preview();

    return 0;
}
