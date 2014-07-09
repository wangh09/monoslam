#include "ZeNanTracker.h"

ZeNanTracker::ZeNanTracker(void)
{
	_TrackCnt = 0;
	_FeatureIdxCnt = 0;

	nearest_num=0;
	nearest_dx=new int[4*nearest_range*nearest_range];
	nearest_dy=new int[4*nearest_range*nearest_range];

	int* tmp_r=new int[4*nearest_range*nearest_range];
	//get dx,dy within a circle area of 0.
	for(int dx=-nearest_range;dx<=nearest_range;dx++)
	{
		for(int dy=-nearest_range;dy<=nearest_range;dy++)
		{
			if((tmp_r[nearest_num]=dx*dx+dy*dy)<nearest_range*nearest_range)
			{
				nearest_dx[nearest_num]=dx;
				nearest_dy[nearest_num]=dy;
				nearest_num++;
			}
		}
	}
	//sort 
	for(int i=0;i<nearest_num-1;i++)
	{
		for(int j=i+1;j<nearest_num;j++)
		{
			if(tmp_r[i]>tmp_r[j])
			{
				int tmp=tmp_r[i];
				tmp_r[i]=tmp_r[j];
				tmp_r[j]=tmp;

				tmp=nearest_dx[i];
				nearest_dx[i]=nearest_dx[j];
				nearest_dx[j]=tmp;

				tmp=nearest_dy[i];
				nearest_dy[i]=nearest_dy[j];
				nearest_dy[j]=tmp;
			}
		}
	}
	delete[] tmp_r;
	int curP=0;
	partical_num=partical_rNum*partical_tNum*partical_tNum;
	partical_dx=new float[partical_num];
	partical_dy=new float[partical_num];
	partical_cosr=new float[partical_num];
	partical_sinr=new float[partical_num];
	for(int txi=-partical_tNum/2;txi<=partical_tNum/2;txi++)
	{
		for(int tyi=-partical_tNum/2;tyi<=partical_tNum/2;tyi++)
		{
			for(int tri=-partical_tNum/2;tri<=partical_tNum/2;tri++)
			{
				partical_dx[curP]=txi*2*partical_tRange/partical_tNum;
				partical_dy[curP]=tyi*2*partical_tRange/partical_tNum;
				partical_cosr[curP]=cos(tri*2*partical_rRange/partical_rNum/180.0*3.1415926);
				partical_sinr[curP]=sin(tri*2*partical_rRange/partical_rNum/180.0*3.1415926);
				curP++;
			}
		}
	}
}
ZeNanTracker::~ZeNanTracker(void)
{
}

TrackInfo* ZeNanTracker::Track(TrackGraph* _Cache,int Frame_Ref,int Frame_)
{
	//Firstly, the camera pose is guessed through a camera motion model
	TrackInfo * newEdge = GuessCamMotion(_Cache->_EdgeCache,Frame_Ref,Frame_);

	//Secondly, using the guessed camera pose, match the features (using a camera motion constraint in feature matching）.
	MatchFeatures(newEdge,_Cache->_NodeCache,Frame_Ref,Frame_);

	//Thirdly, refine the Tf using the information of matched features.
	RefineTf(newEdge,_Cache->_NodeCache,Frame_Ref,Frame_);

	//Finally, allocate FeatureIdx to good feature points.
	AllocFeatIdx(newEdge,_Cache->_NodeCache,Frame_Ref,Frame_);

	return newEdge;
}
TrackInfo * ZeNanTracker::GuessCamMotion(TrackInfo **TrackCache,int Frame_Ref,int Frame_)
{
	TrackInfo* track_result = new TrackInfo();
	track_result->TrackIdx = _TrackCnt;
	_TrackCnt++;
	return track_result;
}
void ZeNanTracker::MatchFeatures(TrackInfo *TrackCache, FrameFeatDes** _NodeCache,int Frame_Ref,int Frame_)
{
	calcTf(TrackCache,_NodeCache,Frame_Ref,Frame_);
}
void ZeNanTracker::RefineTf(TrackInfo *TrackCache, FrameFeatDes** _NodeCache,int Frame_Ref,int Frame_)
{
	//RANSAC for Fundmental Matrix, exclude outlier




	return;
}
void ZeNanTracker::AllocFeatIdx(TrackInfo* newEdge,FrameFeatDes** _NodeCache,int Frame_Ref,int Frame_)
{

	FrameFeatDes* Node_ = _NodeCache[Frame_];
	FrameFeatDes* Node_Ref = _NodeCache[Frame_Ref];
	int FeatureCnt = Node_->nFeatures;
	int temp;
	//因为总是从新的node向旧的node寻找特征点，这样做可以隔着几帧track到特征点
	for(int i =0;i<FeatureCnt;i++)
	{
		if(newEdge->_Match[i]>=0)
		{
			if((temp=Node_Ref->global_FeatureIdx[newEdge->_Match[i]])>=0)
			{
				Node_->global_FeatureIdx[i] = temp;
			}
			else
			{
				Node_Ref->global_FeatureIdx[newEdge->_Match[i]] = _FeatureIdxCnt;
				Node_->global_FeatureIdx[i] = _FeatureIdxCnt;
				_FeatureIdxCnt++;
			}
		}
	}
}


TrackInfo* ZeNanTracker::calcTf(TrackInfo * TrackCache, FrameFeatDes** _NodeCache,int Frame_Ref,int Frame_)
{
	TrackInfo* track_result = TrackCache;
	int RefFeats = _NodeCache[Frame_Ref]->nFeatures;
	int ftRefPrj_x,ftRefPrj_y;
	int** prjFtIdx=new int*[2];prjFtIdx[0]=new int[RefFeats];prjFtIdx[1]=new int[RefFeats];
	int** matchIdx = new int*[2];matchIdx[0]=new int[RefFeats];matchIdx[1]=new int[RefFeats];
	int best_partical = 0;
	int matchNum[2];
	int temp_idx;
	for(int pi=0;pi<partical_num;pi++)
	{
		matchNum[1-best_partical]=0;
		for(int i=0;i<RefFeats;i++)
		{
			if(_NodeCache[Frame_Ref]->feat_idx[i]>=0)
			{
				temp_idx = matchNum[1-best_partical];
				ftRefPrj_x=
					(int)(_NodeCache[Frame_Ref]->FeaturePoints[i].pt.x*partical_cosr[pi]
				-_NodeCache[Frame_Ref]->FeaturePoints[i].pt.y*partical_sinr[pi]+partical_dx[pi]+0.5);
				ftRefPrj_y=(int)(_NodeCache[Frame_Ref]->FeaturePoints[i].pt.x*partical_sinr[pi]+
					_NodeCache[Frame_Ref]->FeaturePoints[i].pt.y*partical_cosr[pi]+partical_dy[pi]+0.5);		

				if(ftRefPrj_x<0||ftRefPrj_x>=iWidth
					||ftRefPrj_y<0||ftRefPrj_y>=iHeight)
				{
					continue;
				}
				int nearestFtIdx=FindNearest(ftRefPrj_x,ftRefPrj_y, _NodeCache[Frame_]);
				if(nearestFtIdx>=0)
				{
					prjFtIdx[1-best_partical][temp_idx]=i;
					matchIdx[1-best_partical][temp_idx] = nearestFtIdx;
					matchNum[1-best_partical]++;
				}
			}
		}
		if(matchNum[1-best_partical]>matchNum[best_partical])
		{
			best_partical = 1-best_partical;
		}
	}
	if(matchNum[best_partical]>=5)
	{
		track_result->MatchCnt = matchNum[best_partical];
		for(int i=0;i<matchNum[best_partical];i++)
			track_result->_Match[matchIdx[best_partical][i]] = prjFtIdx[best_partical][i];
		track_result->isMatched = true;
	}
	delete[] prjFtIdx[0];
	delete[] prjFtIdx[1];
	delete[] prjFtIdx;
	delete[] matchIdx[0];
	delete[] matchIdx[1];
	delete[] matchIdx;

	track_result->Frame_Ref = Frame_Ref;
	track_result->Frame_ = Frame_;
	return track_result;
}
int ZeNanTracker::FindNearest(int cftx,int cfty,FrameFeatDes* key)
{
	int nearestIdx;
	int nearestFtIdx;
	for(nearestIdx=0;nearestIdx<nearest_num;nearestIdx++)
	{
		int nearestx=cftx+nearest_dx[nearestIdx];
		int nearesty=cfty+nearest_dy[nearestIdx];

		if(nearestx<0||nearestx>=iWidth||nearesty<0||nearesty>=iHeight)
		{
			continue;
		}
		if((nearestFtIdx=key->imgFeatIndex[nearestx][nearesty])>=0)
		{
			break;
		}
	}
	if(nearestIdx<nearest_num)
	{
		//find a nearest match
		return nearestFtIdx;
	}
	else
	{
		return -1;
	}

}