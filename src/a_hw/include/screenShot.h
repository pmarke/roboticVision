#include "opencv2/opencv.hpp"
#include <X11/Xlib.h>
#include <X11/Xutil.h>


class ScreenShot
{

private:
	int _x;      // start x pos of screen to grab
	int _y;      // start y pos of screen to grab
	int _width;  // end x pos of screen to grab
	int _height; // end y pos of screen to grab
	XImage* _img;
	Display* _display;
	Window _root;
    


public:
	ScreenShot(int x, int y, int width, int height);
	ScreenShot(int x, int y);
	ScreenShot();
	void getImage(cv::Mat& cvImg);
	~ScreenShot();
	int getHeight();
	int getWidth();


};