module;
#include <vector>
#include <string>
#include <opencv2/imgcodecs.hpp>
#include <fstream>
#include <filesystem>
#include <stdexcept>
#include <iostream>
module ImageParser;
import RGB;

ImageParser::ImageParser(std::string_view fileName) : IParser(fileName)
{
}

std::vector<std::vector<RGB>> ImageParser::parse()
{	
	if (!std::filesystem::exists(fileName))
	{
		throw std::runtime_error("The given file does not exist. Check the path to the given image!");
	}

	auto matrix = cv::imread(fileName.data());

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

void ImageParser::writeImage(std::vector<std::vector<RGB>> buffer, std::string const& fileName)
{
	cv::Mat imgToWrite(cv::Size(buffer[0].size(), buffer.size()), CV_8UC3);

	for (int y = 0; y < imgToWrite.rows; y++)
	{
		for (int x = 0; x < imgToWrite.cols; x++)
		{
			imgToWrite.at<cv::Vec3b>(cv::Point{ y, x }) = cv::Vec3b{ buffer[y][x].B, buffer[y][x].G, buffer[y][x].R };
		}
	}

	cv::imwrite("output.png", imgToWrite);
}
