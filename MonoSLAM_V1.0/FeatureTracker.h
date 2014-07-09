#pragma once
#include "TrackInfo.h"
#include "FeatureHeads.h"
#include<opencv2/opencv.hpp>
#include<opencv2/nonfree/features2d.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<vector>
#include "TrackGraph.h"
#include"Paras.h"
#include "Tracker.h"
#include "ZeNanTracker.h"
class FeatureTracker
{
public:
	FeatureTracker(void);
	~FeatureTracker(void);
	Tracker* m_tracker;
	void InitialTracker(TRACKERTYPE m_trackertype,int iwidth,int iheight);
	TrackInfo* Track(TrackGraph* _Cache,int Frame_Ref,int Frame_);
};