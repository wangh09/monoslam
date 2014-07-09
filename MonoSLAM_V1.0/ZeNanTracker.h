#pragma once
#include "tracker.h"
class ZeNanTracker :
	public Tracker
{
private:
	static const int nearest_range=10;
	static const int partical_tRange=15;
	static const int partical_rRange=15;
	static const int partical_tNum=1;
	static const int partical_rNum=1;
	int* nearest_dx;
	int* nearest_dy;
	int nearest_num;
	float* partical_dx;
	float* partical_dy;
	float* partical_cosr;
	float* partical_sinr;
	int partical_num;
public:
	ZeNanTracker(void);
	~ZeNanTracker(void);
	TrackInfo* Track(TrackGraph* _Cache,int Frame_Ref,int Frame_);
	TrackInfo * GuessCamMotion(TrackInfo **TrackCache,int Frame_Ref,int Frame_);
	void MatchFeatures(TrackInfo *TrackCache, FrameFeatDes** _NodeCache,int Frame_Ref,int Frame_);
	void RefineTf(TrackInfo *TrackCache, FrameFeatDes** _NodeCache,int Frame_Ref,int Frame_);
	void AllocFeatIdx(TrackInfo* newEdge,FrameFeatDes** _NodeCache,int Frame_Ref,int Frame_);

	TrackInfo * MatchTwoFrame(FrameFeatDes** _NodeCache,int Frame_Ref,int Frame_);
	TrackInfo* calcTf(TrackInfo *TrackCache,FrameFeatDes** _NodeCache,int Frame_Ref,int Frame_);   //SHI Zenan's idea
	int FindNearest(int cftx,int cfty,FrameFeatDes* key);
};

