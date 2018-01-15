#include <featureCapture.h>

FeatureCapture::FeatureCapture(){
	
	 // create a private node handle for use with param server
  	ros::NodeHandle nh_private("~");

    dynamic_reconfigure::Server<feature_capture::cornerHarrisConfig> server;
    // dynamic_reconfigure::Server<feature_capture::cornerHarrisConfig>::CallbackType f;


  	// auto func = std::bind(&VisualFrontend::callback_reconfigure, this, std::placeholders::_1, std::placeholders::_2);

    auto func =std::bind(&FeatureCapture::callback,this, std::placeholders::_1, std::placeholders::_2);
    // server.setCallback(func);
    
    _img = cv::imread("/home/mark/projects/roboticVision/src/featureCapture/src/pattern.png");
    cv::cvtColor(_img,_grayImg,cv::COLOR_BGR2GRAY);
    _dst = cv::Mat::zeros(_img.size(),CV_32FC1);
     

    _blockSize = 7;
    _ksize = 3;
    _k = 0.05;
    _borderType = cv::BORDER_DEFAULT;

    namedWindow("corners_window",cv::WINDOW_AUTOSIZE);

    findFeatures();

}

void FeatureCapture::callback(feature_capture::cornerHarrisConfig &config, uint32_t level){

	_blockSize = config.block_size;
	_ksize = config.ksize;
	_k = config.k;
	_borderType = config.border_type;

	findFeatures();
}

void FeatureCapture::findFeatures(){

	// Detetcting corners
	cv::cornerHarris(_grayImg,_dst,_blockSize,_ksize,_k,_borderType);

	// Normalizing
	normalize(_dst, _dst_norm, 0, 255, cv::NORM_MINMAX, CV_32FC1, cv::Mat());
	_imgCopy = _img.clone();

	for(int j = 0; j < _dst_norm.rows; j++)
	{
		for(int i = 0; i <_dst_norm.cols; i++)
		{
			if((int) _dst_norm.at<float>(j,i) > _thresh ){
				cv::circle(_imgCopy, cv::Point(i,j),5,cv::Scalar(204,102,0),2,2,0);
			}
		}
	}

	
	cv::imshow("corners_window", _imgCopy);
	cv::waitKey(0);

}

FeatureCapture::~FeatureCapture(){};


	







	



	