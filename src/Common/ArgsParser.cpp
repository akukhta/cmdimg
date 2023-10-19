module;
#include <stdexcept>
#include <cstring>
#include <functional>
module ArgsParser;

ArgsParser::ArgsParser(int argc, char** argv) : argc(argc), argv(argv),
	argsCop
	{
		std::bind(&ArgsParser::defHandler, this, "--border", std::placeholders::_1, std::ref(_border)),
		std::bind(&ArgsParser::defHandler, this, "--showfps", std::placeholders::_1, std::ref(_fps)),
		std::bind(&ArgsParser::defHandler, this, "--nofpslock", std::placeholders::_1, std::ref(_nofpslock)),
	}
{
	_fileName = argv[1];
	
	for (size_t i = 2; i < argc; i++)
	{
		for (auto& handler : argsCop)
		{
			handler(argv[i]);
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
