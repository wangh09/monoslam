#pragma once
#include<opencv2/opencv.hpp>
#include<opencv2/nonfree/features2d.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<vector>
#include "Paras.h"
using namespace std;
using namespace cv;
class FrameFeatDes
{
public:
	FrameFeatDes(){imgFeatIndex=new int[1024][1024];}
	~FrameFeatDes(){delete imgFeatIndex;}
public:
	IplImage*			_Frame;
	vector<KeyPoint>	FeaturePoints;
	vector<int>			edgeList;
	int					feat_idx[5000];
	int					global_FeatureIdx[5000];
	int					nFeatures;
	int					(*imgFeatIndex)[1024];
	FEATUREDESCRIPTOR	descriptor_type;
	virtual vector<float> getDescriptor(int index){vector<float> s;return s;}
	virtual void calcDescriptor(Mat srcMat){};
	virtual int FilterCorners(){return 0;};
};

