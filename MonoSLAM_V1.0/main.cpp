#pragma once
#include "TrackGraph.h"
#include "FrameCapture.h"
#include "FeatureHandler.h"
#include "FeatureTracker.h"
#include "Paras.h"
#include <iostream>
using namespace std;
void main()
{
//****************************************
//Definitions
//****************************************
	FrameCapture m_FrameCapture;
	TrackGraph m_Cache;
	FeatureHandler m_FeatureHandler;
	FeatureTracker m_Tracker;
	int Index_keyframe = 0;
	int CurrentFrame = 0;
	double track_tf[6];
	track_tf[0]=1;
	track_tf[1]=0;
	track_tf[2]=0;
	track_tf[3]=0;
//****************************************
//Frame Source Setting
//****************************************
	if(!m_FrameCapture.Initial(FROM_AVI_VIDEO,"D:\\a2.avi"))
	{

		cout<<"Open AVI Error!"<<endl;
		return;
	}
//****************************************
//Initializing
//****************************************
	m_FeatureHandler.Initial(FAST_FEATURE,SHITOMASI_DESCRIPTOR);
	m_Tracker.InitialTracker(ZENAN_TRACKER,m_FrameCapture.iWidth,m_FrameCapture.iHeight);
//****************************************
//MainLoop
//****************************************
	while(true)
	{
		//Timer
		//...

		//get one frame
		m_FrameCapture.Capture();
		CurrentFrame = m_FrameCapture.currentFrame;
		//deDistortion
		//...
		
		//detect feature points, create a node.
		m_FeatureHandler.detect(m_FrameCapture.frame);
		m_Cache.storeNode(m_FeatureHandler.m_FeatDes);

		if(CurrentFrame == 0)//when starting, no feature matching
			continue;

		//Feature Tracking
		m_Cache.storeEdge(m_Tracker.Track(&m_Cache,CurrentFrame-1,CurrentFrame));

		//Output Feature Matching
		TrackInfo *p;
		vector<int> edgeList = m_Cache.getNode(CurrentFrame)->edgeList;
		for(int j = 0;j<edgeList.size();j++)
		{
			p = m_Cache.getEdge(edgeList[j]);
			if(p->Frame_Ref==CurrentFrame-1)break;
		}

		IplImage* showMatchResult=cvCreateImage(cvSize(m_FrameCapture.iWidth,m_FrameCapture.iHeight),IPL_DEPTH_8U,3);
		cvCopy(m_Cache.getNode(CurrentFrame-1)->_Frame,showMatchResult);

		if(p->isMatched)
		{
			FrameFeatDes * feat_ref = m_Cache.getNode(p->Frame_Ref);
			FrameFeatDes * feat_	 = m_Cache.getNode(p->Frame_);
			m_Cache.getNode(p->Frame_);
			for(int i=0;i<feat_->nFeatures;i++)
			{
				if(p->_Match[i]>=0)
				{
					CvPoint key_feat=cvPoint(feat_->FeaturePoints[i].pt.x,feat_->FeaturePoints[i].pt.y);
					CvPoint ref_feat=cvPoint(feat_ref->FeaturePoints[p->_Match[i]].pt.x,feat_ref->FeaturePoints[p->_Match[i]].pt.y);
					cvCircle(showMatchResult,ref_feat,5,cvScalar(0,0,255));
					cvCircle(showMatchResult,key_feat,5,cvScalar(0,0,255));
					cvLine(showMatchResult,ref_feat,key_feat,cvScalar(0,255,0));
				}
			}
		}
		cvShowImage("FeaturedImg",showMatchResult);
		waitKey(0);
	}
	
}