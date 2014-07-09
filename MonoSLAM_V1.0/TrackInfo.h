#pragma once
#include "Paras.h"
#include <string.h>
//un-direct graph
class TrackInfo {
public:
	int		TrackIdx;

	int*	_Match;
	float	tf[12];   //9 + 3
	int		MatchCnt;
	int		Frame_Ref;
	int		Frame_;
	bool	isMatched;
	TrackInfo(){_Match = new int[nFeatureSize];memset(_Match,0xff,sizeof(int)*nFeatureSize);
	isMatched = false;}
	~TrackInfo(){delete _Match;}
};