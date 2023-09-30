#pragma once
#include <windows.h>
#include <utility>

class Dimentions
{
public:
	Dimentions() = delete;
	
	static std::pair<size_t, size_t> get(bool border)
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;

		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		return std::make_pair((csbi.srWindow.Right - csbi.srWindow.Left + 1) * brailleDotMultiplier.first,
			(csbi.srWindow.Bottom - csbi.srWindow.Top - (border ? 3 : 1)) * brailleDotMultiplier.second);
	}

	static inline std::pair<int, int> const brailleDotMultiplier = std::make_pair(2, 4);
};