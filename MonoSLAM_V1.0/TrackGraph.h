#pragma once
#include "FeatureHeads.h"
#include "TrackInfo.h"
#include "Paras.h"
#include<opencv2/opencv.hpp>
class TrackGraph {
	public:
		TrackGraph(void);
		~TrackGraph(void);
	private:
		int latestFrame;
	public:
		FrameFeatDes**		_NodeCache;
		TrackInfo**			_EdgeCache;

	public:
		void storeNode(FrameFeatDes * src);
		void storeEdge(TrackInfo * src);
		FrameFeatDes* getNode(int frame);
		TrackInfo* getEdge(int frame);
};