#include <memory>
#include <vector>
#include <iostream>
#include "opencv2/core/utils/logger.hpp"
#include "Dimentions.hpp"
import ArgsParser;
import MediaPreviewer;

int main(int argc, char** argv)
{
    cv::utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT);

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
