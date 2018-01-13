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
	XFixesCursorImage *xfcursorImage = XFixesGetCursorImage(_display);

	// printf("size: %lu \n", sizeof(_*img->data)/sizeof(*_img->data[0]));

	cv::Mat cursorImage(xfcursorImage->width+xfcursorImage->xhot, xfcursorImage->height+xfcursorImage->yhot,CV_8UC4, xfcursorImage->pixels);
	
	// cv::Mat test(_height,_width, CV_8UC4, xfcursorImage->pixels);
	// printf("Height: %i\n", xfcursorImage->width);
	// printf("Width: %i\n", xfcursorImage->height);
	// printf("x: %i\n", xfcursorImage->x);
	// printf("y: %i\n", xfcursorImage->y);
	// printf("hot x: %i\n", xfcursorImage->xhot);
	// printf("hot y: %i\n", xfcursorImage->yhot);

	// cv::Vec4b intensity = cursorImage.at<cv::Vec4b>(0,0);
	// printf("blue %i\n", intensity[0]);
	// printf("green %i\n", intensity[1]);
	// printf("red %i\n", intensity[2]);



	// printf("mat height %i \n", cvImg.height);
	// printf("mat width %i \n", cvImg.width);

	cv::Vec4b color_white={250,250,250,1};
	cv::Vec4b color_teal={0,100,100,1};



	int row,col;

	// for(int i = 2000; i< 3000; i++){
	// 	printf("%i\n",i );
	// 	cvImg.at(0, i);

	// }

	for(int r = 0; r< 24; r++){
		for(int c=0; c<24; c++){
			
				// intensity = cursorImage.at<cv::Vec4b>(r,c);
			if(_mouse[r][c]!=0)
			{
				row = r+xfcursorImage->y;
				col = c+xfcursorImage->x;
				// printf("col: %i\n", col);
				if(row < _height && col < _width){
					cvImg.at<cv::Vec4b>(cv::Point(col,row))= (_mouse[r][c] == 2) ? color_teal:color_white;
				}
			}
			
		}
	}

	// printf("window height %i \n", cvImg.rows);
	// printf("window width %i \n", cvImg.cols);

	// cv::namedWindow("window",cv::WINDOW_AUTOSIZE);
	// cv::imshow("window",cvImg);
	// cv::waitKey(0);
	
}


ScreenShot::~ScreenShot(){
	XDestroyImage(_img);
	XCloseDisplay(_display);
}

	int ScreenShot::getHeight(){return _height;}
	int ScreenShot::getWidth(){return _width;}