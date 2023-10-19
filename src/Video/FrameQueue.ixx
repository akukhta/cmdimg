module;
#include <queue>
#include <mutex>
export module FrameQueue;
import IFrameBuffer;

export class FrameQueue : public IFrameBuffer
{
public:
	FrameQueue(size_t maxFrames);

	virtual void addFrame(frame const& fr) override;
	virtual frame getFrame() override;

private:
	std::queue<frame> frames;
	size_t maxFrames;
	std::mutex bufferMutex;
	std::condition_variable cv;
};