#pragma once
#include <chrono>

class TimeManager
{
public:

	TimeManager() = default;

	void reset()
	{
		seed = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
	}

	std::chrono::microseconds getDelta()
	{
		auto curr = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
		auto rv = curr - seed;
		
		seed = curr;
		
		return rv;
	}

private:
	std::chrono::microseconds seed;
};