module;
#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"  // for Button, Horizontal, Renderer
#include "ftxui/component/component_base.hpp"      // for ComponentBase
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for separator, gauge, text, Element, operator|, vbox, border
#include "ftxui/dom/canvas.hpp"
#include "../Common/TimeManager.hpp"
#include <vector>
#include <thread>
#include <mutex>

export module FXTVideoPrinter;
import RGB;
import IPrinter;
import fpscounter;
import FrameQueue;

export class FXTVideoPrinter : public IPrinter
{
public:
	FXTVideoPrinter(std::pair<size_t, size_t> const& dims, std::unique_ptr<IParser> parser, bool borderEnabled = false);
	void print() override;
	
	void unlockFPS(bool val);
	void showFPS(bool val);

private:
	void parseFrame();

	ftxui::ScreenInteractive* screen;
	std::jthread frameParsingThread;
	std::mutex printerMutex;
	std::condition_variable cv;
	std::chrono::microseconds timePerFrame;
	TimeManager tManager;
	FPSCounter fpscounter;
	FrameQueue frameBuffer;
	
	int fps;
	bool nofpslock;
	bool fpsShow;

	static inline size_t const maxFramesInBuffer = 60;
};