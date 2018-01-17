#include <featureCapture.h>

FeatureCapture::FeatureCapture(){
	
	 // create a private node handle for use with param server
  	ros::NodeHandle nh_private("~");

    
  	auto f = std::bind(&FeatureCapture::callback,this, std::placeholders::_1, std::placeholders::_2);
  	server.setCallback(f);


    _img = cv::imread("/home/mark/projects/roboticVision/src/featureCapture/src/house.jpeg");
   	
   	 cv::cvtColor(_img,_grayImg,cv::COLOR_BGR2GRAY); // convert image to gray
    _dst = cv::Mat::zeros(_img.size(),CV_32FC1);     // empty image

    _imgCopy = _img.clone();
    init = true;

   
     

}

void FeatureCapture::callback(feature_capture::featureDetectionAlgorithmConfig &config, uint32_t level){

	_featureDetectionAlgorithm = static_cast<FeatureDetectionAlgorithms>(config.algorithms);


	// update values
	switch(_featureDetectionAlgorithm)
	{
		case FeatureDetectionAlgorithms::CORNER_HARRIS :
		{
			_cornerHarris.blockSize = config.ch_blockSize;
			_cornerHarris.ksize = config.ch_ksize;
			_cornerHarris.k = config.ch_k;
			_cornerHarris.borderType = config.ch_borderType;
			_cornerHarris.threshold = config.ch_threshold;

			if(init == true) findFeaturesCornerHarris();
			break;
		}
		case FeatureDetectionAlgorithms::GOOD_FEATURES_TO_TRACK :
		{
			_gftt.maxCorners = config.gftt_maxCorners;
			_gftt.qualityLevel = config.gftt_qualityLevel;
			_gftt.minDistance = config.gftt_minDistance;
			_gftt.blockSize = config.gftt_blockSize;
			_gftt.useHarrisDetector = config.gftt_useHarrisDetector;
			_gftt.k = config.gftt_k;

			if(init == true) findFeaturesGFTT();
			break;
		}
		case FeatureDetectionAlgorithms::FAST :
		{
			_fastDetector->setThreshold(config.fast_threshold);
			_fastDetector->setNonmaxSuppression(config.fast_nonmaxSupression);
			_fastDetector->setType(config.fast_types);
			if(init == true) findFeaturesFAST();
			break;
		}
		default:
		{
			printf("Error: Feature Algorithm not found.\n");
			break;
		}
	}
	

	
}

void FeatureCapture::findFeaturesCornerHarris(){
	_imgCopy = _img.clone();

	// Detetcting corners
	cv::cornerHarris(_grayImg,_dst,_cornerHarris.blockSize,_cornerHarris.ksize,_cornerHarris.k,_cornerHarris.borderType);

	// Normalizing
	normalize(_dst, _dst_norm, 0, 255, cv::NORM_MINMAX, CV_32FC1, cv::Mat());
	;

	for(int j = 0; j < _dst_norm.rows; j++)
	{
		for(int i = 0; i <_dst_norm.cols; i++)
		{
			if((int) _dst_norm.at<float>(j,i) > _cornerHarris.threshold ){
				cv::circle(_imgCopy, cv::Point(i,j),5,cv::Scalar(204,102,0),2,2,0);
			}
		}
	}
	cv::imshow("corners_window", _imgCopy);
	cv::waitKey(30);	

}

void FeatureCapture::findFeaturesGFTT(){
	_imgCopy = _img.clone();

	cv::goodFeaturesToTrack(_grayImg,_gftt.corners,_gftt.maxCorners,_gftt.qualityLevel,_gftt.minDistance,cv::Mat(),_gftt.blockSize,_gftt.useHarrisDetector,_gftt.k);
	
	for(int i = 0; i < _gftt.corners.size(); i++){ // draw in the circles
		cv::circle(_imgCopy, _gftt.corners[i], 5, cv::Scalar(204,102,0),2,2,0);
	}
	cv::imshow("corners_window", _imgCopy);
	cv::waitKey(30);

}

void FeatureCapture::findFeaturesFAST(){
	_imgCopy = _img.clone();

	// _fastKeypoints.clear();
	_fastDetector->detect(_grayImg,_fastKeypoints,cv::Mat());

	for(int i = 0; i < _fastKeypoints.size(); i++){ // draw in the circles
		cv::circle(_imgCopy, _fastKeypoints[i].pt, 5, cv::Scalar(204,102,0),2,2,0);
	}
	cv::imshow("corners_window", _imgCopy);
	cv::waitKey(30);

}

void FeatureCapture::imShowLoop(){

	while(true){
		if(init){

			cv::imshow("corners_window", _imgCopy);
			cv::waitKey(30);
		}

	}


}

FeatureCapture::~FeatureCapture(){};


	







	



	