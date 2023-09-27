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
	void compress(size_t width, size_t height);
	void compressBilinear(size_t width, size_t height);
	void compressLanczos(size_t width, size_t height);

	std::vector<std::vector<RGB>> compressedImage;
private:
	std::vector<std::vector<RGB>> image;
};