module;
#include <vector>
#include <string>
export module IParser;
import RGB;

export class IParser
{
public:
	IParser(std::string_view fileName) : fileName(fileName) {};
	virtual std::vector<std::vector<RGB>> parse() = 0;
protected:
	std::string_view fileName;
};