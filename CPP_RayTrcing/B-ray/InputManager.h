#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

struct InputManager
{
	InputManager(float ar,int wd):aspect_ratio(ar), image_width(wd), image_height(static_cast<int>(wd/ ar)){}
	float aspect_ratio;
	int image_width;
	int image_height;

};

#endif // !IMAGE_H
