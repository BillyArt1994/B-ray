#ifndef IMAGE_H
#define IMAGE_H

struct Image
{
	Image(float ar, int width) :aspect_ratio(ar),
		image_width(width),image_height(static_cast<int>(width / ar) {}

	float aspect_ratio;
	int image_width;
	int image_height;

};
#endif // !IMAGE_H

