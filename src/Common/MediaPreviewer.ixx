module;
#include <utility>
#include <string_view>
#include <memory>
export module MediaPreviewer;
import ArgsParser;
import IPrinter;

export class MediaPreviewer
{
public:
	MediaPreviewer(ArgsParser &args);

	void preview();
private:
	std::string_view fileName;
	std::pair<size_t, size_t> dimentions;
	std::unique_ptr<IPrinter> printer;
};