#include "screenShot.h"



ScreenShot::ScreenShot(int x, int y, int width, int height){
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	_display = XOpenDisplay(nullptr);
	_root = DefaultRootWindow(_display);


}

ScreenShot::ScreenShot(int x, int y)
{

	_display = XOpenDisplay(nullptr);
	_root = DefaultRootWindow(_display);
	XWindowAttributes attributes = {0};
	XGetWindowAttributes(_display, _root, &attributes);
	_x = x;
	_y = y;
	_width = attributes.width;
	_height = attributes.height;
}

ScreenShot::ScreenShot()
{

	_display = XOpenDisplay(nullptr);
	_root = DefaultRootWindow(_display);
	XWindowAttributes attributes = {0};
	XGetWindowAttributes(_display, _root, &attributes);
	_x = 0;
	_y = 0;
	_width = attributes.width;
	_height = attributes.height;
}


void ScreenShot::getImage(cv::Mat& cvImg){
	_img = XGetImage(_display,_root,_x,_y,_width,_height,AllPlanes,ZPixmap);
	cvImg = cv::Mat(_height,_width,CV_8UC4, _img->data);
}


ScreenShot::~ScreenShot(){
	XDestroyImage(_img);
	XCloseDisplay(_display);
}

	int ScreenShot::getHeight(){return _height;}
	int ScreenShot::getWidth(){return _width;}