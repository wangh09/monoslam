#pragma once
#include "FrameFeatDes.h"
class Descriptor_ShiTomasi : public FrameFeatDes
{
	vector<float> ShiTomasi;
public:
	Descriptor_ShiTomasi(void);
	~Descriptor_ShiTomasi(void);
	vector<float> getDescriptor(int index);
	void calcDescriptor(Mat srcMat);
	int FilterCorners();
};