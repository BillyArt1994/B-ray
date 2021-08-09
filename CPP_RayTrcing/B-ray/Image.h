#ifndef IMAGE_H
#define IMAGE_H

struct Image
{
	Image(float ar,int wd):aspect_ratio(ar), image_width(wd), image_height(static_cast<int>(wd/ ar)){}

	float aspect_ratio;
	int image_width;
	int image_height;


};

#endif // !IMAGE_H
