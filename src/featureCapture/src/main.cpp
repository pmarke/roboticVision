#include "featureCapture.h"
#include <ros/ros.h>



int main(int argc, char **argv){


	ros::init(argc,argv,"feature_capture");

	FeatureCapture featureCapture;

    ros::spin();
    return 0;

}



