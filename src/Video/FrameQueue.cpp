module;
#include <mutex>
#include <condition_variable>
#include <optional>
module FrameQueue;

FrameQueue::FrameQueue(size_t maxFrames) : maxFrames(maxFrames)
{

}

void FrameQueue::addFrame(frame fr)
{
	std::unique_lock lk(bufferMutex);
	cv.wait(lk, [&]{return frames.size() <= maxFrames; });
	frames.push(std::move(fr));
	cv.notify_one();
}

std::optional<IFrameBuffer::frame> FrameQueue::getFrame()
{
	std::unique_lock lk(bufferMutex);
	
	if (cv.wait_for(lk, std::chrono::seconds(1), [&] {return frames.empty() == false; }))
	{
		auto fr = frames.front();
		frames.pop();
		cv.notify_one();
		return fr;
	}
	else
	{
		throw std::nullopt;
	}
}



