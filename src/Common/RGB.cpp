module;
#include <cassert>
module RGB;
import <algorithm>;

RGB::RGB(std::initializer_list<unsigned char> l)
{
		assert(l.size() == 3);
		unsigned char indx = 0;
		
		for (auto val : l)
		{
			rgb[indx++] = val;
		}
}

RGB& RGB::operator/(double val)
{
	std::for_each(rgb, rgb + 3, [val](auto& x) {x /= val; });
	return *this;
}

RGB& RGB::operator/=(double val)
{
	std::for_each(rgb, rgb + std::size(rgb), [val](auto& x) {x /= val; });
	return *this;
}

RGB& RGB::operator+=(RGB const& other)
{
	for (unsigned char i = 0; i < std::size(rgb); i++)
	{
		rgb[i] += other.rgb[i];
	}

	return *this;
}

RGB operator*(RGB& pixel, double val)
{
	return RGB{ static_cast<unsigned char>(static_cast<double>(pixel.R) * val),
		static_cast<unsigned char>(static_cast<double>(pixel.G) * val),
		static_cast<unsigned char>(static_cast<double>(pixel.B) * val)};
}