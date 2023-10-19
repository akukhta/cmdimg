module;
#include <atomic>
#include <thread>
export module fpscounter;

export class FPSCounter
{
public:
	FPSCounter() = default;

	void run();
	void inc();
	size_t getFPS();

private:
	std::atomic_size_t frames;
	std::atomic_size_t lastfps;

	std::jthread thread;

	void fpsThreadFunc();
};