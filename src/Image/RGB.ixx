module;
export module RGB;
import <initializer_list>;

export struct RGB
{
	RGB(std::initializer_list<unsigned char> l);
	RGB() : R(0), G(0), B(0) {};

	union
	{
		unsigned char rgb[3];

		struct
		{
			unsigned char R;
			unsigned char G;
			unsigned char B;
		};
	};

	RGB& operator/(double val);
	RGB& operator/=(double val);
	RGB& operator+=(RGB const& other);
	friend RGB operator*(RGB& pixel, double val);
};