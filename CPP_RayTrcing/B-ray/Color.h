#ifndef COLOR_H
#define COLOR_H

#include "Vector3.h"
#include "Math.h"

Color write_color(Color &pixel_color) {
	// Write the translated [0,255] value of each color component.
	//auto r = pixel_color.x();
	//auto g = pixel_color.y();
	//auto b = pixel_color.z();

	//auto scale = 1.0f / samples_pixel;
	//r *= scale;
	//g *= scale;
	//b *= scale;
	clamp(pixel_color.x,0.0f,0.999f);
	clamp(pixel_color.y,0.0f,0.999f);
	clamp(pixel_color.z,0.0f,0.999f);

	//pixel_color.x(r);
	//pixel_color.y(g);
	//pixel_color.z(b);

	return pixel_color *= 255.999f;
}
#endif