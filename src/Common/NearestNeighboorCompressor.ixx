module;
#include <vector>
#include <cassert>
export module imageCompressor;
import <algorithm>;
import RGB;

export class ImageCompressor
{
public:
	ImageCompressor(std::vector<std::vector<RGB>> imageMatrix);
	void print(std::vector<std::vector<RGB>> ImageCompressor::*vecRef = &ImageCompressor::image);
	
	std::vector<std::vector<RGB>> compress(size_t width, size_t height);
	std::vector<std::vector<RGB>> compressBilinear(size_t width, size_t height);
	std::vector<std::vector<RGB>> compressLanczos(size_t width, size_t height);

private:
	std::vector<std::vector<RGB>> image;
};