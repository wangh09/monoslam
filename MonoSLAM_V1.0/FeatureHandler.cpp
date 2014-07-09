#include "FeatureHandler.h"


FeatureHandler::FeatureHandler(void)
{
	m_Detector = 0;
	m_FeatDes = 0;
	FeaturedImg = 0;
}
FeatureHandler::~FeatureHandler(void)
{
}
void FeatureHandler::Initial(FEATUREDETECTOR detector_type,FEATUREDESCRIPTOR descriptor_type)
{
	if(m_Detector)delete m_Detector;
	switch(detector_type)
	{
		case FAST_FEATURE:
			m_Detector = new FastFeatureDetector(20,true);
			break;
	}
	this->detector_type = detector_type;
	this->descriptor_type = descriptor_type;
}

int FeatureHandler::detect(IplImage *img)
{
	curImg = img;
	Mat srcMat = Mat(img);
//****************************************
//Initial featDes  !!Note that, delete is the duty of TrackGraph!!!
//Every Loop, the old pointer is passed to TrackGraph
//FrameFeatDes is used to store Feature & Descriptor Info.
//****************************************
	switch(descriptor_type)
	{
		case SHITOMASI_DESCRIPTOR:
			m_FeatDes = new Descriptor_ShiTomasi;
			break;
	}
	m_FeatDes->_Frame = cvCloneImage(img);
//****************************************
//Extract Feature Points
//****************************************
	m_FeatDes->FeaturePoints.clear();
	m_Detector->detect(srcMat,m_FeatDes->FeaturePoints);
//****************************************
//Get Descriptors
//****************************************
	m_FeatDes->calcDescriptor(srcMat);
//****************************************
//Filter Corners
//****************************************
	m_FeatDes->FilterCorners();

	return m_FeatDes->nFeatures;
}

IplImage* FeatureHandler::GetFeaturedImg()
{
	if(FeaturedImg)
	{
		cvReleaseImage(&FeaturedImg);
	}

	FeaturedImg = cvCreateImage(Mat(curImg).size(),IPL_DEPTH_8U,3);

	cvCopy(curImg,FeaturedImg,NULL);

	for(int i=0;i<m_FeatDes->nFeatures;i++)
	{
		if(m_FeatDes->feat_idx[i]>0)
		{
			cvCircle(FeaturedImg,m_FeatDes->FeaturePoints[m_FeatDes->feat_idx[i]].pt,1,Scalar(0,0,255),-1);
		}
	}

	return FeaturedImg;
}