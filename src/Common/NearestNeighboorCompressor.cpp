module;
#include <iostream>
#include <format>
#include <cmath>
module imageCompressor;

ImageCompressor::ImageCompressor(std::vector<std::vector<RGB>> imageMatrix) : image(std::move(imageMatrix))
{
	;
}

void ImageCompressor::print(std::vector<std::vector<RGB>> ImageCompressor::*vecRef)
{
	for (auto& row : this->*vecRef)
	{
		std::cout << "[ ";

		for (auto el : row)
		{
			std::cout << std::format("({}, {}, {})", el.R, el.G, el.B) << " ";
		}

		std::cout << "]\n";
	}
}

std::vector<std::vector<RGB>> ImageCompressor::compress(size_t width, size_t height)
{
	std::vector<std::vector<RGB>> compressed;

	size_t yFactor = image.size() / height;
	size_t xFactor = image[0].size() / width;
	
	for (size_t y = 0; y <= image.size() - yFactor; y += yFactor)
	{
		std::vector<RGB> compressedRow;

		for (size_t x = 0; x <= image[y].size() - xFactor; x += xFactor)
		{
			RGB cPixel{ 0, 0, 0 };

			for (size_t dy = y; dy < y + yFactor; dy++)
			{
				for (size_t dx = x; dx < x + xFactor; dx++)
				{
					cPixel += image[dy][dx] / (xFactor * yFactor);
				}
			}

			compressedRow.push_back(cPixel);
		}

		compressed.emplace_back(std::move(compressedRow));
	}

	return compressed;
}

RGB bilinearInterpolation(const std::vector<std::vector<RGB>>& image, double x, double y)
{
	int x1 = static_cast<int>(x);
	int y1 = static_cast<int>(y);
	
	double fx = x - x1;
	double fy = y - y1;

	if (x1 < 0)
	{
		x1 = 0;
	}
	else if (x1 >= image[0].size() - 1)
	{
		x1 = image[0].size() - 2;
	}
	
	if (y1 < 0)
	{
		y1 = 0;
	} else if (y1 >= image.size() - 1)
	{
		y1 = image.size() - 2;
	}

	const RGB& p1 = image[y1][x1];
	const RGB& p2 = image[y1][x1 + 1];
	const RGB& p3 = image[y1 + 1][x1];
	const RGB& p4 = image[y1 + 1][x1 + 1];

	RGB result{0, 0,0};
	result.R = static_cast<uint8_t>(
		(1.0 - fx) * (1.0 - fy) * p1.R + fx * (1.0 - fy) * p2.R + (1.0 - fx) * fy * p3.R + fx * fy * p4.R
		);
	result.G = static_cast<uint8_t>(
		(1.0 - fx) * (1.0 - fy) * p1.G + fx * (1.0 - fy) * p2.G + (1.0 - fx) * fy * p3.G + fx * fy * p4.G
		);
	result.B = static_cast<uint8_t>(
		(1.0 - fx) * (1.0 - fy) * p1.B + fx * (1.0 - fy) * p2.B + (1.0 - fx) * fy * p3.B + fx * fy * p4.B
		);

	return result;
}

std::vector<std::vector<RGB>> ImageCompressor::compressBilinear(size_t width, size_t height)
{
	const int resizedWidth = width;
	const int resizedHeight = height;
	const int originalWidth = image[0].size();
	const int originalHeight = image.size();

	std::vector<std::vector<RGB>> compressed(resizedHeight, std::vector<RGB>(resizedWidth));

	for (int y = 0; y < resizedHeight; y++) {
		for (int x = 0; x < resizedWidth; x++) {
			double originalX = static_cast<double>(x) * (static_cast<double>(originalWidth) / static_cast<double>(resizedWidth));
			double originalY = static_cast<double>(y) * (static_cast<double>(originalHeight) / static_cast<double>(resizedHeight));

			compressed[y][x] = bilinearInterpolation(image, originalX, originalY);
		}
	}

	return compressed;
}

double const PI = 3.14159265;

double lfKernel(double x, int a)
{
	if (x == 0)
	{
		return 1;
	}
	else if (x >= -1 && x < a)
	{
		return (a * std::sin(PI * x) * std::sin((PI * x) / a)) / (std::pow(PI, 2) * std::pow(x, 2));
	}
	else
	{
		return 0;
	}
}

std::vector<std::vector<RGB>> ImageCompressor::compressLanczos(size_t width, size_t height)
{
	std::vector<std::vector<RGB>> compressed(height, std::vector<RGB>(width));

	double resizeFactorX = static_cast<double>(image[0].size()) / width;
	double resizeFactorY = static_cast<double>(image.size()) / height;

	const int a = 3;

	for (size_t y = 0; y < height; y++) {
		for (size_t x = 0; x < width; x++) {
			double xOrig = x * resizeFactorX;
			double yOrig = y * resizeFactorY;

			int x_min = std::max(static_cast<int>(xOrig) - a + 1, 0);
			int x_max = std::min(static_cast<int>(xOrig) + a, static_cast<int>(image[0].size()));
			int y_min = std::max(static_cast<int>(yOrig) - a + 1, 0);
			int y_max = std::min(static_cast<int>(yOrig) + a, static_cast<int>(image.size()));

			RGB pixel;
			double total_weight{ 0.0 };

			for (int j = y_min; j < y_max; j++) {
				for (int i = x_min; i < x_max; i++) {
					double dx = xOrig - i;
					double dy = yOrig - j;

					double weight = lfKernel(dx, a) * lfKernel(dy, a);
					pixel += image[j][i] * weight;
					total_weight += weight;
				}
			}

			pixel /= total_weight;

			compressed[y][x] = pixel;
		}
	}

	return compressed;
}

