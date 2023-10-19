module;
#include <stdexcept>
#include <cstring>
#include <functional>
module ArgsParser;

ArgsParser::ArgsParser(int argc, char** argv) : argc(argc), argv(argv),
	argsCop
	{
		{"--border", &_border},
		{"--showfps", &_fps},
		{"--nofpslock", &_nofpslock}
	}
{
	_fileName = argv[1];
	
	for (size_t i = 2; i < argc; i++)
	{
		if (auto it = argsCop.find(argv[i]); it != argsCop.end())
		{
			*it->second = true;
		}
	}
}

bool ArgsParser::border()
{
	return _border;
}

bool ArgsParser::fps()
{
	return _fps;
}

bool ArgsParser::nofpslock()
{
	return _nofpslock;
}

std::string_view ArgsParser::fileName()
{
	if (_fileName.empty())
	{
		throw std::runtime_error("Filename is not specified");
	}

	return _fileName;
}
