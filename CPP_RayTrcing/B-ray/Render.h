#ifndef RENDER_H
#define RENDER_H

#include <iostream>
#include "svpng.h"
#include "Camera.h"
#include "Image.h"
#include "Light.h"
#include "Color.h"
#include "Mesh.h"
#include "Ray.h"

class Render
{
public:
	Render(Camera& m_camer,Image& m_image,Mesh& m_mesh,Light& m_light):camera(m_camer),
		image(m_image), mesh(m_mesh), light(m_light),rgb(new unsigned char[m_image.image_width*m_image.image_height * 3]){}

	void Rendering();
	void SaveTexture();

private:
	unsigned char *rgb;
	Camera camera;
	Image image;
	Mesh mesh;
	Light light;

	Vector3 ray_color();
};

void Render::Rendering() {
	unsigned width = image.image_width;
	unsigned height = image.image_height;
	Vector3 high_left_corner = camera.high_left_corner;
	Vector3 horizontal = camera.horizontal;
	Vector3 vertical = camera.vertical;
	Vector3 camerPos = camera.cameraPosition;
	for (unsigned i = 0; i < height; i++) {

		for (unsigned j = 0; j < width; j++) {
			auto u = float(j) / (width - 1);
			auto v = float(i) / (height - 1);
			Ray r(camerPos, ((high_left_corner + horizontal * u - vertical * v) - camerPos).normalize());
			Color pixel_color = ray_color();
			write_color(std::cout, pixel_color);
			*rgb++ = (unsigned char)pixel_color.x();    //R
			*rgb++ = (unsigned char)pixel_color.y();    //G
			*rgb++ = (unsigned char)pixel_color.z();    //B
		}

		if (i % 2 == 0)
		{
			int rate =static_cast<int>(floor(i*(100.0f/(height - 1))));
			std::cout << rate << "%" << std::endl;
		}
	}
}

void Render::SaveTexture() {
	FILE *fp = fopen("render.png", "wb");
	svpng(fp, image.image_width, image.image_height, rgb, 0);
	fclose(fp);
}

Vector3 Render::ray_color() {

}

#endif // !RENDER_H

