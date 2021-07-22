#ifndef IMAGE_H
#define IMAGE_H

class Image
{
public:
	Image(float aspect_ratio, int image_width) :
		_aspect_ratio(aspect_ratio),
		_image_width(image_width),
		_image_height(static_cast<int>(image_width / aspect_ratio)) {}

	float GetRatio() const { return _aspect_ratio; }
	int GetWidth() const { return _image_width; }
	int GetHeight() const { return _image_height; }

private:
	float _aspect_ratio;
	int _image_width;
	int _image_height;
};

#endif // !IMAGE_H

