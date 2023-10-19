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
        screen(nullptr), frameBuffer(maxFramesInBuffer)
{
    frameParsingThread = std::jthread(std::bind(&FXTVideoPrinter::parseFrame, this));

    if (auto vp = dynamic_cast<VideoParser*>(this->parser.get()))
    {
        fps = vp->getFPS();
        timePerFrame = std::chrono::microseconds(1000000) / fps;
        fpscounter.run();
    }
}

void FXTVideoPrinter::print()
{
    ftxui::Component rendererFrame;
    
    if (nofpslock == false)
    {
        rendererFrame = ftxui::Renderer([&] {
            auto c = ftxui::Canvas(dims.first, dims.second);
            {
                tManager.reset();
                
                auto frameToDraw = frameBuffer.getFrame();

                if (frameToDraw)
                {
                    for (int y = 0; y < dims.second; y++)
                    {
                        for (int x = 0; x < dims.first; x++)
                        {
                            auto& pixel = frameToDraw.value()[y][x];
                            c.DrawPoint(x, y, true, ftxui::Color(pixel.R, pixel.G, pixel.B));
                        }
                    }

                    screen->PostEvent(ftxui::Event{});
                    fpscounter.inc();
                }
                

                auto dT = tManager.getDelta();

                if (dT < timePerFrame)
                {
                    auto v = timePerFrame - dT;
                    std::this_thread::sleep_for(v / 10);
                }
            }

            if (borderEnabled)
            {
                return canvas(std::move(c)) | ftxui::border;
            }
            else
            {
                return canvas(std::move(c));
            }

            });
    }
    else
    {
        rendererFrame = ftxui::Renderer([&] {
            auto c = ftxui::Canvas(dims.first, dims.second);
            {
                auto frameToDraw = frameBuffer.getFrame();

                if (frameToDraw)
                {
                    for (int y = 0; y < dims.second; y++)
                    {
                        for (int x = 0; x < dims.first; x++)
                        {
                            auto& pixel = frameToDraw.value()[y][x];
                            c.DrawPoint(x, y, true, ftxui::Color(pixel.R, pixel.G, pixel.B));
                        }
                    }

                    fpscounter.inc();
                    screen->PostEvent(ftxui::Event{});
                }
                cv.notify_one();

                auto dT = tManager.getDelta();
            }

            if (borderEnabled)
            {
                return canvas(std::move(c)) | ftxui::border;
            }
            else
            {
                return canvas(std::move(c));
            }

            });
    }

    ftxui::Component hc;

    if (fpsShow)
    { 
        auto renderer_text = ftxui::Renderer([&] {
            auto c = ftxui::Canvas(20, 20);
            c.DrawText(0, 0, std::format("FPS: {}", fpscounter.getFPS()));
            return canvas(std::move(c));
            });

        hc = ftxui::Container::Horizontal({ rendererFrame, renderer_text });
    }
    else
    {
        hc = ftxui::Container::Horizontal({ rendererFrame });
    }

    auto component = ftxui::Container::Horizontal({
        hc
        });

    auto component_renderer = Renderer(component, [&] {
        return component->Render();
        });

    screen = new ftxui::ScreenInteractive{ ftxui::ScreenInteractive::FitComponent() };
    screen->Loop(component_renderer);
}

void FXTVideoPrinter::unlockFPS(bool val)
{
    nofpslock = val;
}

void FXTVideoPrinter::showFPS(bool val)
{
    fpsShow = val;
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
            frameBuffer.addFrame(std::move(compressor.compressBilinear(dims.first, dims.second)));
        }
    }
    screen->Exit();
}
