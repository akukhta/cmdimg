module;
#include <vector>
#include <string>
export module ImageParser;
import IParser;
import RGB;

export class ImageParser : public IParser
{
public:
	ImageParser(std::string_view fileName);
	virtual std::vector<std::vector<RGB>> parse() override;
	void writeImage(std::vector<std::vector<RGB>> buffer, std::string const& fileName);
};