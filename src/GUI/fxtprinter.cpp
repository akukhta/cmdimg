module;
#include <vector>
#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"  // for Button, Horizontal, Renderer
#include "ftxui/component/component_base.hpp"      // for ComponentBase
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for separator, gauge, text, Element, operator|, vbox, border
#include "ftxui/dom/canvas.hpp"
#include <cassert>
module FXTPrinter;
import RGB;

FXTPrinter::FXTPrinter(std::pair<size_t, size_t> const& dims) : dims(dims) {}

void FXTPrinter::print(std::vector<std::vector<RGB>> const &image)
{
    using namespace ftxui;
    auto c = Canvas(dims.first, dims.second);
    
    assert(image.size() == dims.second);
    assert(image[0].size() == dims.first);

    for (int y = 0; y < dims.second; y++)
    {
        for (int x = 0; x < dims.first; x++)
        {
            auto &pixel = image[y][x];
            c.DrawPoint(x, y, true, Color(pixel.R, pixel.G, pixel.B));
        }
    }

    auto document = canvas(&c) | border;

    auto screen = Screen::Create(Dimension::Fit(document));
    
    Render(screen, document);
    screen.Print();
}