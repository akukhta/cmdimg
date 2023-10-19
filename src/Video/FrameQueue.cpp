module;
#include <mutex>
#include <condition_variable>
module FrameQueue;

FrameQueue::FrameQueue(size_t maxFrames) : maxFrames(maxFrames)
{

}

void FrameQueue::addFrame(frame const& fr)
{
	std::unique_lock lk(bufferMutex);
	cv.wait(lk, [&]{return frames.size() <= maxFrames; });
	frames.push(std::move(fr));
}

IFrameBuffer::frame FrameQueue::getFrame()
{
	std::unique_lock lk(bufferMutex);
	cv.wait(lk, [&] {return frames.empty() == false; });

	auto fr = frames.front();
	frames.pop();

	return fr;
}



