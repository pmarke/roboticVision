#include "opencv2/opencv.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <screenShot.h>

#define KEY_Q 113
#define KEY_S 115


int main(int, char**){

	ScreenShot screen;
	cv::Mat img;
	cv::VideoCapture cap(0);  // open the default camera
	bool webcam = false;
	int key;
	if(!cap.isOpened()) // chek if connection to camera succeeded
	{
		printf("Could not connect to webcam!\n");
		return -1;
	}
	else
	{
		printf("Connected to webcam");
	}

	cv::namedWindow("img",0);  //Display image in this window
	cv::moveWindow("img",screen.getWidth()*(1-1.1/6.0),screen.getHeight()*(1-1.1/6.0));
	cv::resizeWindow("img",screen.getWidth()/6,screen.getHeight()/6);


	// while(true){
	// 	cap.read(frame);  // read in camera image and store it in frame
	// 	cv::imshow("edges", frame);
	// 	if(cv::waitKey(30)>= 0)
	// 		break;
	// }


while(true){


if(webcam){
	cap.read(img);
}
else{
	screen.getImage(img);
	// cap.grab();
}
cv::imshow("img",img);
key = cv::waitKey(30);
if(key == KEY_Q){
	break;
}
else if(key == KEY_S)
{
	webcam = !webcam;
}

if(key >= 0){
	printf("key %i\n", key);
}

// key=cv::waitKey(0);

}



return 0;

}