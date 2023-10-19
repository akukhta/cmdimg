module;
#include <vector>
export module IFrameBuffer;
import RGB;

export class IFrameBuffer
{
public:
	using frame = std::vector<std::vector<RGB>>;
	virtual void addFrame(frame const&) = 0;
	virtual frame getFrame() = 0;
};