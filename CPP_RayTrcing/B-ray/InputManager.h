#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

struct InputManager
{
	InputManager(float ar,int wd):aspect_ratio(ar), image_width(wd), image_height(static_cast<int>(wd/ ar)){}
	float aspect_ratio;
	unsigned image_width, image_height;
};

#endif // !IMAGE_H
