#include <iostream>
#include "svpng.h"
#include "Vector3.h"

int main() {

	// Image

	const auto aspect_ratio = 16 / 9;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width/ image_height);

	//Camera
	auto cameraPos = Vector3 (0);
	

	// Render
	RenderTex();
	return 0;
}

void RenderTex() {
	unsigned char rgb[256 * 256 * 3], *p = rgb;
	unsigned x, y;
	FILE *fp = fopen("rgb.png", "wb");
	for (y = 0; y < 256; y++)
		for (x = 0; x < 256; x++) {
			*p++ = (unsigned char)x;    /* R */
			*p++ = (unsigned char)y;    /* G */
			*p++ = 128;                 /* B */
		}
	svpng(fp, 256, 256, rgb, 0);
	fclose(fp);
}