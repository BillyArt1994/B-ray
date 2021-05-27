#ifndef RENDER_H
#define RENDER_H
#include <iostream>
#include "svpng.h"

class Render
{
public:
	Render() {
		unsigned char rgb[400 * 225 * 3], *p = rgb;
		for (int i = 0; i < image_height; i++) {
			for (int j = 0; j < image_width; j++) {
				auto u = double(j) / (image_width - 1);
				auto v = double(i) / (image_height - 1);
				Ray r(mainCamera.GetPos(), (high_left_corner + horizontal * u - vertical * v - cameraPos).normalize());
				Color pixel_Color = ray_color(r, obj);
				write_color(std::cout, pixel_Color);

				*p++ = (unsigned char)pixel_Color.x();    //R
				*p++ = (unsigned char)pixel_Color.y();    //G
				*p++ = (unsigned char)pixel_Color.z();    //B
			}

			if (i % 22 == 0)
			{
				int rate = ceil(i*(100.0f / (image_height - 1)));
				std::cout << rate << "%" << std::endl;
			}
		}
		RenderTex(image_width, image_height, rgb);
	};

private:

	void RenderTex(const unsigned image_width, const unsigned image_height, const unsigned char *rgb) {
		FILE *fp = fopen("render.png", "wb");
		svpng(fp, image_width, image_height, rgb, 0);
		fclose(fp);
	}

};

#endif // !RENDER_H

