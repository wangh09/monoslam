#pragma once
#include "Paras.h"
#include<opencv2/opencv.hpp>
class FrameCapture
{
public:
	int iWidth;
	int iHeight;

public:
	FrameCapture(void);
	~FrameCapture(void);
	bool Initial(FRAMESOURCE s);
	bool Initial(FRAMESOURCE s,const char* fileName);
	bool Capture();
	void Clear();
private:
	CvCapture* capture;
	FRAMESOURCE source_ref;
public:
	IplImage *frame;
	int currentFrame;
};

