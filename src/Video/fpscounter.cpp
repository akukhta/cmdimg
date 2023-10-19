module;
#include <thread>
#include <chrono>
module fpscounter;

void FPSCounter::run()
{
	thread = std::jthread(&FPSCounter::fpsThreadFunc, this);
}

void FPSCounter::inc()
{
	frames++;
}

size_t FPSCounter::getFPS()
{
	return lastfps.load();
}

void FPSCounter::fpsThreadFunc()
{
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		lastfps.store(frames);
		frames.store(0);
	}
}
