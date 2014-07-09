#include "TrackGraph.h"
using namespace std;
TrackGraph::TrackGraph(void)
{
	_NodeCache = new FrameFeatDes*[CacheSize];
	_EdgeCache = new TrackInfo*[TrackCacheSize];
	for(int i=0;i<CacheSize;i++)
	{
		_NodeCache[i] = 0;
	}
	for(int i =0;i<TrackCacheSize;i++)
	{
		_EdgeCache[i] = 0;
	}
	latestFrame=-1;
}


TrackGraph::~TrackGraph(void)
{
	for(int i=0;i<CacheSize;i++)
	{
		if(_NodeCache[i])
		{
			delete _NodeCache[i];
		}
		
	}
	for(int i=0;i<TrackCacheSize;i++)
	{
		if(_EdgeCache[i])
		{
			delete _EdgeCache[i];
		}
	}
}

void TrackGraph::storeNode(FrameFeatDes * src)
{
	latestFrame++;
	int storeIdx = latestFrame%CacheSize;
	if(_NodeCache[storeIdx])
	{
		delete _NodeCache[storeIdx];
	}
	_NodeCache[storeIdx] = src;
}
void TrackGraph::storeEdge(TrackInfo * src)
{
	int storeIdx = src->TrackIdx%TrackCacheSize;
	if(_EdgeCache[storeIdx])
	{
		delete _EdgeCache[storeIdx];
	}
	_EdgeCache[storeIdx] = src;
	_NodeCache[src->Frame_%CacheSize]->edgeList.push_back(src->TrackIdx);
	_NodeCache[src->Frame_Ref%CacheSize]->edgeList.push_back(src->TrackIdx);
}
FrameFeatDes* TrackGraph::getNode(int frame)
{
	if(frame>latestFrame||frame<latestFrame-CacheSize+1)
	{
		return 0;
	}
	else
	{
		return _NodeCache[frame%CacheSize];
	}
}
TrackInfo* TrackGraph::getEdge(int edgeidx)
{
	int idx = edgeidx%TrackCacheSize;
	if(!_EdgeCache[idx])
	{
		return 0;
	}
	else
	{
		return _EdgeCache[idx];
	}
}