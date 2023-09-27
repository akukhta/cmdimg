module;
#include <vector>
#include <string>
#include <boost/gil.hpp>
#include <boost/gil/extension/dynamic_image/any_image.hpp>
#include <boost/gil/extension/io/jpeg.hpp>
#include <boost/gil/extension/io/png.hpp>
#include <boost/mpl/vector.hpp>
#include <fstream>
#include <filesystem>
#include <stdexcept>
#include <iostream>
module ImageParser;

struct PixelInserter
{
	PixelInserter(std::pair<size_t, size_t> dimentions) 
		: dimentions(dimentions) {}

	void operator()(boost::gil::rgb8_pixel_t p)
	{
		RGB pixel{ boost::gil::at_c<0>(p), boost::gil::at_c<1>(p), boost::gil::at_c<2>(p) };

		currentRow.push_back(pixel);
		
		if (currentRow.size() == dimentions.first)
		{
			pixels.emplace_back(currentRow);
		}
	}

	std::vector<RGB> currentRow;
	std::vector<std::vector<RGB>> pixels;
	std::pair<size_t, size_t> dimentions;
};

std::vector<std::vector<RGB>> ImageParser::parseImage(std::string_view fileName) const
{
	using namespace boost::gil;
	
	if (!std::filesystem::exists(fileName))
	{
		throw std::runtime_error("The given file does not exist. Check the path to the given image!");
	}

	rgb8_image_t img;
	std::string ext;

	{
		auto pos = fileName.find_last_of(".");
		ext = fileName.substr(pos + 1, fileName.size() - pos);
	}

	try
	{
		if (ext == "png")
		{
			read_image(std::string{ fileName }, img, png_tag{});
		}
		else if (ext == "jpg")
		{
			image_read_settings<jpeg_tag> readSettings;
			read_image(std::string{ fileName }, img, readSettings);
		}
	}
	catch (...)
	{
		std::cout << "Error: Incompatible image type" << std::endl;
		throw;
	}

	auto dims = img.dimensions();
	
	PixelInserter pInserter{ std::make_pair(dims.x, dims.y) };
	
	auto getPixel = [&pInserter](boost::gil::rgb8_pixel_t p)
		{
			RGB pixel{ boost::gil::at_c<0>(p), boost::gil::at_c<1>(p), boost::gil::at_c<2>(p) };

			pInserter.currentRow.push_back(pixel);

			if (pInserter.currentRow.size() == pInserter.dimentions.first)
			{
				pInserter.pixels.emplace_back(std::move(pInserter.currentRow));
			}
		};

	for_each_pixel(const_view(img), getPixel);

	return pInserter.pixels;
}

void ImageParser::writeImage(std::vector<std::vector<RGB>> buffer, std::string const& fileName)
{
	using namespace boost::gil;
	std::vector<rgb8_pixel_t> pixels;

	for (auto& row : buffer)
	{
		for (auto el : row)
		{
			pixels.emplace_back(el.R, el.G, el.B);
		}
	}

	rgb8_view_t img_view = interleaved_view(buffer[0].size(), 
		buffer.size(), reinterpret_cast<rgb8_ptr_t>(&pixels[0]), buffer[0].size() * sizeof(rgb8_pixel_t));

	write_view("output.png", img_view, png_tag());
}
