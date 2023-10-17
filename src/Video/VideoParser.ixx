module;
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>
export module VideoParser;
import IParser;
import RGB;

export class VideoParser : public IParser
{
public:
	VideoParser(std::string_view fileName);
	virtual std::vector<std::vector<RGB>> parse() override;
	int getFPS();

private:
	cv::VideoCapture cap;
};