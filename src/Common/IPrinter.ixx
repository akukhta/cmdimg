module;
#include <vector>
#include <memory>
export module IPrinter;
import RGB;
import IParser;

export class IPrinter
{
public:
	IPrinter(std::pair<size_t, size_t> const& dims, std::unique_ptr<IParser> parser, bool borderEnabled = false)
		: dims(dims), parser(std::move(parser)), borderEnabled(borderEnabled) {};
	
	virtual void print() = 0;

protected:
	std::pair<size_t, size_t> dims;
	std::unique_ptr<IParser> parser;
	bool borderEnabled;
};