#ifndef FEATURE_CAPTURE_H_
#define FEATURE_CAPTURE_H_

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <ros/ros.h>
#include <dynamic_reconfigure/server.h>
#include <feature_capture/featureDetectionAlgorithmConfig.h>
#include <vector>


class FeatureCapture{

private:

	char* _filename;
	cv::Mat _img, _grayImg, _dst, _dst_norm, _imgCopy;

	bool init = false;

	// dynamic reconfigure
	dynamic_reconfigure::Server<feature_capture::featureDetectionAlgorithmConfig> server;

	enum FeatureDetectionAlgorithms{
		CORNER_HARRIS,
		GOOD_FEATURES_TO_TRACK
	} _featureDetectionAlgorithm;

	// Corner Harris algorithm parameters
	struct CornerHarris{ 
		int blockSize;  // Neighborhood size   blockSize X blockSize (pixels)
		int ksize;      // size of the extended sobel kernel. Can be 1,3,5,7. Used to find derivatives
		double k;		// Harris detector free parameter
		int borderType; // Pixel extrapolation method to create pixels
			/*
			 Various border types, image boundaries are denoted with '|'

			 * BORDER_REPLICATE:     aaaaaa|abcdefgh|hhhhhhh
			 * BORDER_REFLECT:       fedcba|abcdefgh|hgfedcb
			 * BORDER_REFLECT_101:   gfedcb|abcdefgh|gfedcba
			 * BORDER_WRAP:          cdefgh|abcdefgh|abcdefg
			 * BORDER_CONSTANT:      iiiiii|abcdefgh|iiiiiii  with some specified 'i'
			 */
		int threshold; // If the coner harris value of a pixel is greater than threshold, display the piexl
	} _cornerHarris;

	std::vector<cv::Point2f> _corners; // vectore to hold the feature points
	struct GoodFeaturesToTrack{ // GFTT algorithm parameters
		int maxCorners;         // Max number of corners that will be detected
		double qualityLevel;	// Minimal accepted quality of image corners
		double minDistance;		// Minimum distance between accepted corners.
		int blockSize;          // Neighborhood size   blockSize X blockSize (pixels)
		bool useHarrisDetector; // Use cornerHarris() == true | cornerMinEigenVal() == false
		double k;               // Harris detector free parameter

	} _gftt;


public:

	FeatureCapture();
	~FeatureCapture();
	void callback(feature_capture::featureDetectionAlgorithmConfig &config, uint32_t level);
	void findFeaturesCornerHarris();
	void findFeaturesGFTT();




};

#endif
