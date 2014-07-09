#include "Descriptor_ShiTomasi.h"


Descriptor_ShiTomasi::Descriptor_ShiTomasi(void)
{
}
Descriptor_ShiTomasi::~Descriptor_ShiTomasi(void)
{
}
void Descriptor_ShiTomasi::calcDescriptor(Mat srcMat)
{
	nFeatures = FeaturePoints.size();
	descriptor_type = SHITOMASI_DESCRIPTOR;
//****************************************
//Get ShiTomasi Score
//****************************************
	Mat desMat = Mat::zeros(srcMat.size(),CV_32FC1);
	Mat srcGray;
	cvtColor(srcMat, srcGray, COLOR_BGR2GRAY );
	cornerMinEigenVal(srcGray,desMat,3,3);
	float tmpDes;
	for(vector<cv::KeyPoint>::iterator iter = FeaturePoints.begin();iter!=FeaturePoints.end();iter++)
	{
		tmpDes = desMat.at<float>((int)iter->pt.y,(int)iter->pt.x);
		ShiTomasi.push_back(tmpDes);
	}
	for(int i=0;i<nFeatures;i++)
		feat_idx[i]=i;
//****************************************
//Sort(Select Sort)
//****************************************
	/*
	float tpMaxTomasi;
	int tpMaxIndex;
	for(int outMax = 0;outMax<nFeatures;outMax++)
	{
		tpMaxTomasi = ShiTomasi[feat_idx[outMax]];
		tpMaxIndex = outMax;
		for(int inMax =outMax+1;inMax<nFeatures;inMax++)
		{
			if(tpMaxTomasi < ShiTomasi[feat_idx[inMax]])
			{
				tpMaxTomasi = ShiTomasi[feat_idx[inMax]];
				tpMaxIndex = inMax;
			}
		}
		if(outMax!=tpMaxIndex)
		{
			int tp =feat_idx[outMax];
			feat_idx[outMax]=feat_idx[tpMaxIndex];
			feat_idx[tpMaxIndex]=tp;
		}
	}
	*/
}
vector<float> Descriptor_ShiTomasi::getDescriptor(int index)
{
	vector<float> result;
	result.push_back(ShiTomasi[index]);
	return result;
}

int Descriptor_ShiTomasi::FilterCorners()
{
	int Thresradilus = 10;
	float ThresStep = (ShiTomasi[0] - ShiTomasi[nFeatures-1])/100;

	memset(&imgFeatIndex[0][0],0xff,sizeof(int)*1024*1024);

	for(int iSel=0;iSel<nFeatures;iSel++)
	{
		if(feat_idx[iSel]==-1||(ShiTomasi[iSel]<ShiTomasi[nFeatures-1]+ThresStep))
		{
			continue;
		}
		for(int iCandi=iSel+1;iCandi<nFeatures;iCandi++)
		{
			if(feat_idx[iCandi]==-1||(ShiTomasi[iSel]-ShiTomasi[iCandi])>ThresStep)
			{
				continue;
			}
			else
			{
				if(((FeaturePoints[iSel].pt.x-FeaturePoints[iCandi].pt.x)*(FeaturePoints[iSel].pt.x-FeaturePoints[iCandi].pt.x)
						+(FeaturePoints[iSel].pt.y-FeaturePoints[iCandi].pt.y)*(FeaturePoints[iSel].pt.y-FeaturePoints[iCandi].pt.y))<Thresradilus*Thresradilus)
					feat_idx[iCandi]=-1;
			}
		}
	}
	
	for(int i=0;i<nFeatures;i++)
	{
		if(feat_idx[i]>=0)
		{
			imgFeatIndex[(int)FeaturePoints[i].pt.x][(int)FeaturePoints[i].pt.y]=i;
		}
	}
	return 0;
}