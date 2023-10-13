module;
#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"  // for Button, Horizontal, Renderer
#include "ftxui/component/component_base.hpp"      // for ComponentBase
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for separator, gauge, text, Element, operator|, vbox, border
#include "ftxui/dom/canvas.hpp"
#include <vector>
export module FXTPrinter;
import RGB;
import IPrinter;

export class FXTPrinter : public IPrinter
{
public:
	FXTPrinter(std::pair<size_t, size_t> const &dims, std::unique_ptr<IParser> parser, bool borderEnabled = false);
	void print() override;
};