#include "opencv2/opencv.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <screenShot.h>
#include <audioRecorder.h>
#include <opencv2/videoio.hpp>  // Video write



#define KEY_Q 113
#define KEY_S 115


int main(int, char**){

	ScreenShot screen;
	cv::Mat img;
	cv::VideoCapture cap(0);      // open the default camera
	cv::VideoWriter videoWriter;
	int codec;
	cv::Size S;

	AudioRecorder audioRecorder("/home/mark/Downloads/test.wav", 1);






	bool webcam = true;
	int key;
	if(!cap.isOpened()) // chek if connection to camera succeeded
	{
		printf("Could not connect to webcam!\n");
		return -1;
	}
	else
	{
		printf("Connected to webcam\n");

		codec = cv::VideoWriter::fourcc('M','J','P','G');
		// codec = cv::VideoWriter::fourcc('P','I','M','1');


		S = cv::Size((int) cap.get(cv::CAP_PROP_FRAME_WIDTH), (int) cap.get(cv::CAP_PROP_FRAME_HEIGHT));

		videoWriter.open("/home/mark/Downloads/test.avi", codec, cap.get(cv::CAP_PROP_FPS),cv::Size(1920,1080),true);

		printf("VideoWriter Opened: %i \n", videoWriter.isOpened());
		printf("fps: %f \n",cap.get(cv::CAP_PROP_FPS) );

		printf("camera width: %i \n", (int) cap.get(cv::CAP_PROP_FRAME_WIDTH));
		printf("camera height: %i \n", (int) cap.get(cv::CAP_PROP_FRAME_HEIGHT));
	}

	cv::namedWindow("img",0);  //Display image in this window
	cv::moveWindow("img",screen.getWidth()*(1-1.1/6.0),screen.getHeight()*(1-1.1/6.0));
	cv::resizeWindow("img",screen.getWidth()/6,screen.getHeight()/6);


	audioRecorder.startStream();

	while(true){


		if(cap.read(img)) // if their is a new image
		{
			// This is inside the other if statement to ensure screen shots
			// are grabbed at the same rate as the camera.
			if(!webcam){
				screen.getImage(img);
				// cv::Mat test(cv::Size((int) big_image.rows, (int) big_image.cols),CV_8UC3);
				cv::cvtColor(img,img,cv::COLOR_BGRA2BGR,3);
				cv::imshow("img",img);
				videoWriter.write(img);
				

			}
			else{

				cv:resize(img,img, cv::Size(1440,1080));
				cv::Mat big_image = cv::Mat::zeros(1080,1920,img.type());
				img.copyTo(big_image(cv::Rect(240,0,img.cols,img.rows)));
				cv::imshow("img",big_image);
				videoWriter.write(big_image);
				
			}
			
			
		}


		key = cv::waitKey(1);
		if(key == KEY_Q){
			videoWriter.release();
			audioRecorder.stopStream();
			audioRecorder.writeToFile();
			cap.release();
			break;
		}
		else if(key == KEY_S)
		{
			webcam = !webcam;
		}

		if(key >= 0){
			printf("key %i\n", key);
		}




	}





	return 0;

}