#pragma once
#include<opencv2/opencv.hpp>
#include<opencv2/nonfree/features2d.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<vector>
using namespace std;
using namespace cv;
class FeatureDetector
{
public:
	FeatureDetector(void);
	~FeatureDetector(void);
	int detect(IplImage *img,bool Equ=false);
};

