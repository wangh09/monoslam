#pragma once
#include "Paras.h"
#include<opencv2/opencv.hpp>
class VideoCapture
{
public:
	static int iWidth;
	static int iHeight;

public:
	void Initial(FRAMESOURCE s,const char* fileName);
	VideoCapture(void);
	~VideoCapture(void);
	bool Capture();
	bool CaptureFromAVI();
	bool CaptureOneFrameFromeAVI();
	void EndCaptureFromAVI();
private:
	CvCapture* capture;
	FRAMESOURCE source_ref;
	char fileName[100];
public:
	IplImage *frame;
	int currentFrame;
};

