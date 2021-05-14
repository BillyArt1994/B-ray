#include "svpng.h"
#include "Vector3.h"
#include "Color.h"
#include "Ray.h"
#include <iostream>

double hit_sphere(const Vector3 &center,double radius,const Ray&r) {
	Vector3 oc = r.GetOriginPos() - center;
	auto a = dot(r.GetDirection(), r.GetDirection());
	auto b = 2.0*dot(oc, r.GetDirection());
	auto c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a*c;
	if (discriminant<0)
	{
		return -1.0;
	}
	else
	{
		return (-b-sqrt(discriminant))/(2.0*a);
	}
	
}

Color ray_color(Ray r) {
	auto t =hit_sphere(Vector3(0, 0, -1), 0.5, r);
	if (t >0.0) {
		Vector3 normal = (r.RayRun(t) - Vector3(0, 0, -1)).normalize();
		return Color(normal.x() + 1, normal.y() + 1, normal.z() + 1)*0.5;
	}	
	Vector3 dir = r.GetDirection();
	t = (dir.y() + 1)*0.5;
	return Color(1.0, 1.0, 1.0)*(1.0 - t) + Color(0.5, 0.7, 1.0)*t;
}

void RenderTex(unsigned image_width, unsigned image_height, unsigned char *rgb) {
	FILE *fp = fopen("render.png", "wb");
	svpng(fp, image_width, image_height, rgb, 0);
	fclose(fp);
}

int main() {
	// Image
	const auto aspect_ratio = 16.0 / 9.0;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width / aspect_ratio);

	//Camera
	auto viewport_height = 2.0;
	auto viewport_width = aspect_ratio * viewport_height;
	auto focal_length = 1.0;

	auto cameraPos = Vector3(0);
	auto horizontal = Vector3(viewport_width, 0, 0);
	auto vertical = Vector3(0, viewport_height, 0);
	auto high_left_corner = cameraPos - horizontal / 2 + vertical / 2 - Vector3(0, 0, focal_length);

	// Render
	unsigned char rgb[400 * 711 * 3], *p = rgb;
	for (int i = 0; i < image_height; i++)
		for (int j = 0; j < image_width; j++) {
			auto u = double(j) / (image_width - 1);
			auto v = double(i) / (image_height - 1);
			Ray r(cameraPos, high_left_corner + horizontal * u - vertical * v - cameraPos);
			Color pixel_Color = ray_color(r);
			write_color(std::cout, pixel_Color);
			*p++ = (unsigned char)pixel_Color.x();    /* R */
			*p++ = (unsigned char)pixel_Color.y();    /* G */
			*p++ = (unsigned char)pixel_Color.z();    /* B */
		}
	RenderTex(image_width, image_height, rgb);
	return 0;
}
