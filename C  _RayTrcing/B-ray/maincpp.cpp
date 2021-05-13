#include "svpng.h"
#include "Vector3.h"
#include "Color.h"
#include "Ray.h"
#include <iostream>

Color x() {

}

int main(){
	// Image
	const auto aspect_ratio = 16 / 9;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width/ aspect_ratio);

	//Camera
	auto viewport_height = 2.0;
	auto viewport_width = aspect_ratio * viewport_height;
	auto focal_length = 1.0;

	auto cameraPos = Vector3(0);
	auto horizontal = Vector3(viewport_width, 0, 0);
	auto vertical = Vector3(0, viewport_height, 0);
	auto lower_left_corner = cameraPos - horizontal / 2 - vertical / 2 - Vector3(0, 0, focal_length);

	// Render
	unsigned char rgb[400 * 711 * 3], *p = rgb;
	for (int i = 0; i < image_height; i++)
		for (int j = 0; j < image_width; j++) {
			auto u = double(i) / (image_width - 1);
			auto v = double(j) / (image_height - 1);
			Ray r(cameraPos,lower_left_corner+horizontal*u+vertical*v-cameraPos);
			*p++ = 128;    /* R */
			*p++ = 128;    /* G */
			*p++ = 128;                 /* B */
		}
	RenderTex(rgb);
	return 0;
}

void RenderTex(unsigned char *rgb) {
	FILE *fp = fopen("rgb.png", "wb");
	svpng(fp, 256, 256, rgb, 0);
	fclose(fp);
}