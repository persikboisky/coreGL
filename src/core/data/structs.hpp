#ifndef SRC_CORE_DATA_STRUCTS_HPP_
#define SRC_CORE_DATA_STRUCTS_HPP_

struct color_rgb final
{
	float red;
	float green;
	float blue;

	color_rgb() : red(0), green(0), blue(0) {}
	color_rgb(float red, float green, float blue) :
		red(red), green(green), blue(blue)
	{ }
};

struct color_rgba final
{
	float red;
	float green;
	float blue;
	float alpha;

	color_rgba() : red(0), green(0), blue(0), alpha(1.0) { }
	color_rgba(float red, float green, float blue, float alpha) : 
		red(red), green(green), blue(blue), alpha(alpha)
	{ }
};

struct position_2f final
{
	float x = 0;
	float y = 0;

	position_2f() { }
	position_2f(float x, float y) : x(x), y(y) {}
};

struct position_3f final
{
	float x = 0;
	float y = 0;
	float z = 0;

	position_3f() {}
	position_3f(float x, float y, float z) : x(x), y(y), z(z) {}
};

struct position_4f final
{
	float x = 0;
	float y = 0;
	float z = 0;
	float w = 0;

	position_4f() {}
	position_4f(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
};

struct size_2f final
{
	float width = 0;
	float height = 0;

	size_2f() { }
	size_2f(float width, float height) : width(width), height(height)
	{ }
};
	
struct size_3f final
{
	float width = 0;
	float height = 0;
	float length = 0;

	size_3f() { }
	size_3f(float width, float height, float length) : 
		width(width), height(height), length(length)
	{ }
};

#endif // !SRC_CORE_DATA_STRUCTS_HPP_