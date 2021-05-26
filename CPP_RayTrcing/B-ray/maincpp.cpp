#include "svpng.h"
#include "Vector3.h"
#include "Color.h"
#include "Ray.h"
#include "Mesh.h"
#include <iostream>



Color ray_color(Ray& r,Mesh& obj) {
	if (obj.CheckIntersection(r) == true)
	{
		return obj.GetNormal()*0.5f+ Vector3(0.5f,0.5f,0.5f);
	}
	Vector3 dir = r.GetDirection();
	auto t = (dir.y() + 1.0f)*0.5f;
	return Color(1.0f, 1.0f, 1.0f)*(1.0f - t) + Color(0.5f, 0.7f, 1.0f)*t;
}

void RenderTex(unsigned image_width, unsigned image_height, unsigned char *rgb) {
	FILE *fp = fopen("render.png", "wb");
	svpng(fp, image_width, image_height, rgb, 0);
	fclose(fp);
}

int main() {

	Mesh obj = ReadObjFile("C:\\Users\\huang\\Desktop\\Torus.obj");

	// Image
	const auto aspect_ratio = 16.0f / 9.0f;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width / aspect_ratio);

	//Camera
	auto viewport_height = 2.0f;
	auto viewport_width = aspect_ratio * viewport_height;
	auto focal_length = 1.0f;

	auto cameraPos = Vector3(0.0f,0.0f,-7.0f);
	auto horizontal = Vector3(viewport_width, 0.0f, 0.0f);
	auto vertical = Vector3(0.0f, viewport_height, 0.0f);
	auto high_left_corner = cameraPos - horizontal / 2 + vertical / 2 - Vector3(0.0f, 0.0f, focal_length);

	// Render
	unsigned char rgb[400 * 711 * 3], *p = rgb;
	for (int i = 0; i < image_height; i++)
		for (int j = 0; j < image_width; j++) {
			auto u = double(j) / (image_width - 1);
			auto v = double(i) / (image_height - 1);
			Ray r(cameraPos, (high_left_corner + horizontal * u - vertical * v - cameraPos).normalize());
			Color pixel_Color = ray_color(r, obj);
			write_color(std::cout, pixel_Color);
			*p++ = (unsigned char)pixel_Color.x();    //R
			*p++ = (unsigned char)pixel_Color.y();    //G
			*p++ = (unsigned char)pixel_Color.z();    //B
		}
	RenderTex(image_width, image_height, rgb);

	return 0;
}
