#ifndef SCREEN_SHOT_H
#define SCREEN_SHOT_H


#include "opencv2/opencv.hpp"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/Xfixes.h>
#include <X11/extensions/Xrandr.h>


class ScreenShot
{

private:
	int _x;           // start x pos of screen to grab, pixel
	int _y;           // start y pos of screen to grab, pixel
	int _width;       // width of region of interest, pixels
	int _height;      // height of region of interest, pixels
	int _screenWidth; // Width of computer screen, pixels
	int _screenHeight;// Height of computer screen, pixels
	short _screenfps; // current screen fps, hz
	XImage* _img;
	Display* _display;
	Window _root;

	// Open CV color definitions
	cv::Vec4b _color_white={250,250,250,1};
	cv::Vec4b _color_teal={0,100,100,1};

	// Bit map for mouse
	int _mouse[24][24]={{2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					    {2,1,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
						{2,2,1,1,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
						{0,2,1,1,1,1,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
						{0,2,2,1,1,1,1,1,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0},
						{0,0,2,1,1,1,1,1,1,1,2,2,2,0,0,0,0,0,0,0,0,0,0,0},
						{0,0,2,2,1,1,1,1,1,1,1,1,2,2,2,0,0,0,0,0,0,0,0,0},
						{0,0,0,2,1,1,1,1,1,1,1,1,1,1,2,2,0,0,0,0,0,0,0,0},
						{0,0,0,2,2,1,1,1,1,1,1,1,1,1,1,2,2,0,0,0,0,0,0,0},
						{0,0,0,0,2,1,1,1,1,1,1,1,1,1,1,1,2,2,0,0,0,0,0,0},
						{0,0,0,0,2,2,1,1,1,1,1,1,2,2,1,1,1,2,0,0,0,0,0,0},
						{0,0,0,0,0,2,1,1,1,1,1,1,1,2,2,2,2,2,0,0,0,0,0,0},
						{0,0,0,0,0,2,1,1,1,1,2,1,1,1,2,2,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,2,2,1,1,1,2,2,1,1,1,2,2,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,2,1,1,1,2,2,2,1,1,1,2,2,0,0,0,0,0,0},
						{0,0,0,0,0,0,2,2,1,1,1,2,2,2,1,1,1,2,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,2,2,1,1,2,0,2,2,1,1,2,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,2,2,1,2,0,0,2,2,2,2,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
	    


public:

	/*      Different constructors
	x - starting x pixel location from which screen will be grabed. 
	y - starting y pixel location from which screen will be grabed
	width - pixel width of frame that will be grabed
	height - piexl heigt of frame

	getImage will return a height X witdh frame of the computer screen
	starting at (x,y)

	*/
	ScreenShot(int x, int y, int width, int height);
	

	// deflaut constructor will capture entire screen
	ScreenShot();

	// Init screen display and get attributes: _screenWidth, _screenHeight, _fps
	void init();

	// retrieves the screen shot with cursor
	void getImage(cv::Mat& cvImg);
	
	int getHeight();               // return image pixel height
	int getWidth();				   // return image pixel width

	void printAttributes();        // print attributes for debug purposes
	
	int getFPS();

	~ScreenShot();


};

#endif