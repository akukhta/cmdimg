module;
#include <stdexcept>
#include <cstring>
module ArgsParser;

ArgsParser::ArgsParser(int argc, char** argv) : argc(argc), argv(argv)
{	
	_fileName = argc == 1 ? "" : argv[1];

	for (int i = 2; i < argc; i++)
	{
		if (std::strcmp(argv[i], "--border") == 0)
		{
			_border = true;
		}
	}
}

bool ArgsParser::border()
{
	return _border;
}

std::string_view ArgsParser::fileName()
{
	if (_fileName.empty())
	{
		throw std::runtime_error("Filename is not specified");
	}

	return _fileName;
}
