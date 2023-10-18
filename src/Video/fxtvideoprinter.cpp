module;
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/component/mouse.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/canvas.hpp"
#include "ftxui/screen/color.hpp"
#include <vector>
#include <cassert>
#include <stdexcept>
#include <thread>
#include <chrono>
#include <iostream>
#include <functional>
module FXTVideoPrinter;
import imageCompressor;
import VideoParser;

FXTVideoPrinter::FXTVideoPrinter(std::pair<size_t, size_t> const& dims,
    std::unique_ptr<IParser> parser, bool borderEnabled) : IPrinter(dims, std::move(parser), borderEnabled), 
    screen(nullptr), readyToDraw(false), drawn(true)
{
    frameParsingThread = std::jthread(std::bind(&FXTVideoPrinter::parseFrame, this));

    if (auto vp = dynamic_cast<VideoParser*>(this->parser.get()))
    {
        fps = vp->getFPS();
        timePerFrame = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::seconds(1)) / fps;
    }
}

void FXTVideoPrinter::print()
{
    auto rendererFrame = ftxui::Renderer([&] {
        auto c = ftxui::Canvas(dims.first, dims.second);
        {
            std::unique_lock fm(printerMutex);
            cv.wait(fm, [&]() { return readyToDraw; });
            readyToDraw = false;
            
            tManager.reset();
            
            if (!frame.empty())
            {
                for (int y = 0; y < dims.second; y++)
                {
                    for (int x = 0; x < dims.first; x++)
                    {
                        auto& pixel = frame[y][x];
                        c.DrawPoint(x, y, true, ftxui::Color(pixel.R, pixel.G, pixel.B));
                    }
                }
            }

            drawn = true;
            cv.notify_one();

            auto dT = tManager.getDelta();
            
            if (dT < timePerFrame)
            {
                std::this_thread::sleep_for(std::chrono::microseconds(dT) - tManager.getDelta());
            }
        }
        return canvas(std::move(c));
        });


    auto hc = ftxui::Container::Horizontal({ rendererFrame });

    auto component = ftxui::Container::Horizontal({
        hc
        });

    auto component_renderer = Renderer(component, [&] {
        return component->Render();
        });

    screen = new ftxui::ScreenInteractive{ ftxui::ScreenInteractive::FitComponent() };
    screen->Loop(component_renderer);
}

void FXTVideoPrinter::parseFrame()
{
    VideoParser* vParser = dynamic_cast<VideoParser*>(parser.get());

    if (vParser == nullptr)
    {
        throw std::runtime_error("can`t cast IParser to VideoParser");
    }

    while (true)
    {
        auto frame = vParser->parse();

        if (frame.empty())
        {
            break;
        }

        ImageCompressor compressor{ std::move(frame) };
        {
            std::unique_lock fm(printerMutex);
            cv.wait(fm, [&]() { return drawn; });
            drawn = false;
            this->frame = std::move(compressor.compressBilinear(dims.first, dims.second));
            readyToDraw = true;
            screen->PostEvent(ftxui::Event{});
            cv.notify_one();
        }
    }
    screen->Exit();
}
