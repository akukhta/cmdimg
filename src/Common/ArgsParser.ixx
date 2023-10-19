module;
#include <string_view>
#include <unordered_map>
#include <functional>

export module ArgsParser;

export class ArgsParser
{
public:
	ArgsParser(int argc, char** argv);

	bool border();
	bool fps();
	bool nofpslock();

	std::string_view fileName();
private:
	int argc;
	char** argv;
	std::string_view _fileName;

	bool _border = false;
	bool _fps = false;
	bool _nofpslock = false;

	std::unordered_map<std::string_view, bool*> argsCop;
};