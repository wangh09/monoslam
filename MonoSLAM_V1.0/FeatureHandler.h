#pragma once
#include<opencv2/opencv.hpp>
#include<opencv2/nonfree/features2d.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<vector>
#include"Paras.h"
#include "FeatureHeads.h"
using namespace std;
using namespace cv;

class FeatureHandler
{
public:
	FeatureHandler(void);
	~FeatureHandler(void);
public:
	FrameFeatDes*			m_FeatDes;
	FeatureDetector*		m_Detector;
	FEATUREDETECTOR			detector_type;
	FEATUREDESCRIPTOR		descriptor_type;
	IplImage *				curImg;
	IplImage *				FeaturedImg;
public:
	void Initial(FEATUREDETECTOR detector_type,FEATUREDESCRIPTOR descriptor_type);
	int detect(IplImage *img);
	IplImage *GetFeaturedImg();	

};