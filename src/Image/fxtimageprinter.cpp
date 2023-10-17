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
import imageCompressor;

FXTPrinter::FXTPrinter(std::pair<size_t, size_t> const& dims, std::unique_ptr<IParser> parser, bool borderEnabled)
    : IPrinter(dims, std::move(parser), borderEnabled) {}

void FXTPrinter::print()
{
    using namespace ftxui;
    auto c = Canvas(dims.first, dims.second);

    ImageCompressor compressor{ std::move(parser->parse()) };
    auto image = compressor.compressBilinear(dims.first, dims.second);

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

    auto document = canvas(&c);

    if (borderEnabled)
    {
        document |= border;
    }

    auto screen = Screen::Create(Dimension::Fit(document));
    
    Render(screen, document);
    screen.Print();
}