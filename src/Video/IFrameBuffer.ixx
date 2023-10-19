module;
#include <vector>
#include <optional>
export module IFrameBuffer;
import RGB;

export class IFrameBuffer
{
public:
	using frame = std::vector<std::vector<RGB>>;
	virtual void addFrame(frame) = 0;
	virtual std::optional<frame> getFrame() = 0;
};