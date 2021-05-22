#ifndef COLOR_H
#define COLOR_H

#include "Vector3.h"
#include <iostream>

void write_color(std::ostream &out, Color &pixel_color) {
	// Write the translated [0,255] value of each color component.
	pixel_color *= 255.999f;
	//out << static_cast<int>(pixel_color.x()) << ' '
	//	<< static_cast<int>(pixel_color.y()) << ' '
	//	<< static_cast<int>(pixel_color.z()) << '\n';
}
#endif