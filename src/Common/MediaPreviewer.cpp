module;
#include <string_view>
#include "Dimentions.hpp"
module MediaPreviewer;
import PrinterParserFactory;

MediaPreviewer::MediaPreviewer(ArgsParser& args)
{
	auto factory = PrinterParserFactory(args);
	auto dims = Dimentions::get(args.border());
	printer = factory.getPrinter(dims, factory.getParser(), args.border());
}

void MediaPreviewer::preview()
{
	printer->print();
}

