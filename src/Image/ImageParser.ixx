module;
#include <vector>
#include <string>
export module ImageParser;
import RGB;

export class ImageParser
{
public:
	ImageParser() = default;
	std::vector<std::vector<RGB>> parseImage(std::string_view fileName) const;
	void writeImage(std::vector<std::vector<RGB>> buffer, std::string const& fileName);
};