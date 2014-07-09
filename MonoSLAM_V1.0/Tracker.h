#pragma once
#include "TrackInfo.h"
#include "FeatureHeads.h"
#include<opencv2/opencv.hpp>
#include<opencv2/nonfree/features2d.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<vector>
#include "TrackGraph.h"
#include"Paras.h"
class Tracker{
public:
	int iWidth;
	int iHeight;
	int _TrackCnt;
	int	_FeatureIdxCnt;
	virtual TrackInfo* Track(TrackGraph* _Cache,int Frame_Ref,int Frame_){return 0;}
};
