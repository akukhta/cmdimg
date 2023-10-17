module;
#include <string_view>
#include <filesystem>
#include "opencv2/opencv.hpp"
module VideoParser;

VideoParser::VideoParser(std::string_view fileName) : IParser(fileName)
{
	if (!std::filesystem::exists(fileName))
	{
		throw std::runtime_error("The given file does not exist. Check the path to the given image!");
	}

	cap.open(fileName.data());

	if (cap.isOpened() == false)
	{
		throw std::runtime_error("Can`t open video file!");
	}
}


std::vector<std::vector<RGB>> VideoParser::parse()
{
	cv::Mat matrix;
	cap >> matrix;
	
	if (matrix.empty())
	{
		return {};
	}

	std::vector<std::vector<RGB>> image;

	for (int y = 0; y < matrix.rows; y++)
	{
		std::vector<RGB> currentRow;

		for (int x = 0; x < matrix.cols; x++)
		{
			auto& cvpixel = matrix.at<cv::Vec3b>(cv::Point(x, y));
			currentRow.push_back({ cvpixel[2], cvpixel[1], cvpixel[0] });
		}

		image.push_back(std::move(currentRow));
	}

	matrix.release();
	image.shrink_to_fit();
	return std::move(image);
}

int VideoParser::getFPS()
{
	return cap.get(cv::CAP_PROP_FPS);
}
