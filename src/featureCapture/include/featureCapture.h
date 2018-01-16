#ifndef FEATURE_CAPTURE_H_
#define FEATURE_CAPTURE_H_

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <ros/ros.h>
#include <dynamic_reconfigure/server.h>
#include <feature_capture/cornerHarrisConfig.h>


class FeatureCapture{

private:

	char* _filename;
	cv::Mat _img, _grayImg, _dst, _dst_norm, _imgCopy;

					 //corner harris
	int _blockSize;  //neighborhood size   blockSize X blockSize (pixels)
	int _ksize;      // size of the extended sobel kernel. Can be 1,3,5,7. Used to find derivatives
					 // The higher the value allows for more smoothing
	double _k;       // Harris detector free parameter
	int _borderType; // Pixel extrapolation method to create pixels

	/*
	 Various border types, image boundaries are denoted with '|'

	 * BORDER_REPLICATE:     aaaaaa|abcdefgh|hhhhhhh
	 * BORDER_REFLECT:       fedcba|abcdefgh|hgfedcb
	 * BORDER_REFLECT_101:   gfedcb|abcdefgh|gfedcba
	 * BORDER_WRAP:          cdefgh|abcdefgh|abcdefg
	 * BORDER_CONSTANT:      iiiiii|abcdefgh|iiiiiii  with some specified 'i'
	 */

	int _thresh = 200;
	dynamic_reconfigure::Server<feature_capture::cornerHarrisConfig> server;
	// dynamic_reconfigure::Server<feature_capture::cornerHarrisConfig>::CallbackType f;

public:

	FeatureCapture();
	~FeatureCapture();
	void callback(feature_capture::cornerHarrisConfig &config, uint32_t level);
	void findFeatures();



};

#endif
