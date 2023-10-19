module;
#include <memory>
#include <string_view>
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include <set>
export module PrinterParserFactory;

import IParser;
import ImageParser;
import VideoParser;
import IPrinter;
import FXTPrinter;
import FXTVideoPrinter;
import ArgsParser;

export class PrinterParserFactory
{
public:

	PrinterParserFactory(ArgsParser &parser) : argsParser(parser), fileName(argsParser.fileName()), ext(getExtension(fileName)) {}

	std::unique_ptr<IParser> getParser()
	{
		if (imageFormats.find(ext) != imageFormats.end())
		{
			return std::make_unique<ImageParser>(fileName);
		}

		if (videoFormats.find(ext) != videoFormats.end())
		{
			return std::make_unique<VideoParser>(fileName);
		}

		throw std::runtime_error("Unsupported file format!");
	}

	std::unique_ptr<IPrinter> getPrinter(std::pair<size_t, size_t> const& dims,
		std::unique_ptr<IParser> parser, bool borderEnabled = false)
	{
		if (imageFormats.find(ext) != imageFormats.end())
		{
			return std::make_unique<FXTPrinter>(dims, std::move(parser), borderEnabled);
		}
		
		if (videoFormats.find(ext) != videoFormats.end())
		{
			auto vPrinter = std::make_unique<FXTVideoPrinter>(dims, std::move(parser), borderEnabled);
			
			vPrinter->showFPS(argsParser.fps());
			vPrinter->unlockFPS(argsParser.nofpslock());

			return vPrinter;
		}

		throw std::runtime_error("Unsupported file format!");
	}

private:

	static std::string getExtension(std::string_view fileName)
	{
		auto pos = fileName.find_last_of('.');

		if (pos == std::string::npos)
		{
			throw std::runtime_error("Incorrect filename! Please specify extension of the file!");
		}

		std::string ext{ fileName.substr(pos + 1, fileName.size() - pos) };
		std::for_each(ext.begin(), ext.end(), [](auto& x) { x = std::tolower(x); });
		return ext;
	}

	static std::set<std::string_view> inline const imageFormats = 
		{
			"jpg", "jpeg", "jpe", "bmp", "dib", "jp2", "png", "webp", "avif", "pbm", "pgm",
			"ppm", "pxm", "pnm", "pfm", "sr", "ras", "tiff", "tif", "exr", "hdr", "pic"
		};

	static std::set<std::string_view> inline const videoFormats = { "avi" };
	
	ArgsParser &argsParser;
	std::string_view fileName;
	std::string ext;
};