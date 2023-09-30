module;
#include <string_view>
export module ArgsParser;

export class ArgsParser
{
public:
	ArgsParser(int argc, char** argv);

	bool border();
	std::string_view fileName();
private:
	int argc;
	char** argv;
	bool _border = false;
	std::string_view _fileName;
};