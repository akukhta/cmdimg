module;
#include <string_view>
#include <vector>
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

	std::vector<std::function<void(std::string const&)>> argsCop;

	void defHandler(std::string const& arg, std::string_view expectedName, bool& field)
	{
		if (arg == expectedName)
		{
			field = true;
		}
	};
};