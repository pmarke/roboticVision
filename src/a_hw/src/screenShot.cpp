#include "screenShot.h"



ScreenShot::ScreenShot(int x, int y, int width, int height){

	init(); // init screen and get attributes

	// starting pixel locations
	_x = x;
	_y = y;


	// Ensure ROI are within screen dimensions. 
	if(x+width > _screenWidth)
	{
		printf("screenShot::_width ROI outside screen dimensions. Resizing.\n");
		_width = _screenWidth - x;
	}
	else{
		_width = width;
	}

	if(y+height > _screenHeight)
	{
		_height = _screenHeight - x;
		printf("Screen::_height ROI outside screen dimensions. Resizing.\n");
	}
	else{
		_height = height;
	}

	printAttributes();

}



ScreenShot::ScreenShot()
{

	init(); // init screen and get attributes
	_width = _screenWidth;
	_height=_screenHeight;
	_x = 0;
	_y = 0;

	printAttributes();

}

void ScreenShot::init(){
	// open access to the display
	_display = XOpenDisplay(nullptr);
	_root = DefaultRootWindow(_display);

	// get window attributes. We are insterested in width and height
	XWindowAttributes attributes = {0};
	XGetWindowAttributes(_display, _root, &attributes);
	_screenWidth = attributes.width;
	_screenHeight = attributes.height;


	// get fps of the display
	XRRScreenConfiguration *conf = XRRGetScreenInfo(_display,_root);
	_screenfps = XRRConfigCurrentRate(conf);
}


void ScreenShot::getImage(cv::Mat& cvImg){


	// Get screen image and convert it to cv::Mat object
	_img = XGetImage(_display,_root,_x,_y,_width,_height,AllPlanes,ZPixmap);
	cvImg = cv::Mat(_height,_width,CV_8UC4, _img->data);


	// Get cursor information: start x and y position 
	XFixesCursorImage *xfcursorImage = XFixesGetCursorImage(_display);


	// cv::Mat cursorImage(xfcursorImage->width+xfcursorImage->xhot, xfcursorImage->height+xfcursorImage->yhot,CV_8UC4, xfcursorImage->pixels);
	
	// Place the cursor into the base screen image
	int row,col;
	for(int r = 0; r< 24; r++){
		for(int c=0; c<24; c++){
			
			if(_mouse[r][c]!=0)
			{
				row = r+xfcursorImage->y;
				col = c+xfcursorImage->x;
				if(row < _height && col < _width){
					cvImg.at<cv::Vec4b>(cv::Point(col,row))= (_mouse[r][c] == 2) ? _color_teal:_color_white;
				}
			}
			
		}
	}
	
}


ScreenShot::~ScreenShot(){
	
}

void ScreenShot::printAttributes(){


	printf("#######Printing ScreenShot attributes.########\n\n");
	printf("fps: %i\n", (int)_screenfps);
	printf("Max Screen Width (pixel) %i\n", _screenWidth);
	printf("Max Screen Height (pixel) %i\n", _screenHeight);
	printf("Start x pos of screen to grab (pixel): %i\n",_x);
	printf("Start y pos of screen to grab (pixel): %i\n",_y);
	printf("ROI width (pixel): %i\n",_width);
	printf("ROI height(pixel): %i\n\n",_height);
	printf("##############################################\n\n");

}

int ScreenShot::getHeight(){return _height;}
int ScreenShot::getWidth(){return _width;}
int ScreenShot::getFPS(){return (int) _screenfps;} 