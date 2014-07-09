#include "FrameCapture.h"


FrameCapture::FrameCapture(void)
{
	capture=0;
}
FrameCapture::~FrameCapture(void)
{
}
bool FrameCapture::Initial(FRAMESOURCE s)
{
	switch(s)
	{
	case FROM_AVI_VIDEO:
		return false;
		break;
	case FROM_CAMERA:
		break;
	}
	source_ref = s;
	return true;
}
bool FrameCapture::Initial(FRAMESOURCE s,const char* fileName)
{
	switch(s)
	{
	case FROM_AVI_VIDEO:
		currentFrame=-1;
		capture=cvCaptureFromAVI(fileName);
		iWidth = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);
		iHeight = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);  
		if(capture==0)return false;
		break;
	case FROM_CAMERA:
		break;
	}
	source_ref = s;
	return true;
}
bool FrameCapture::Capture()
{
	if(!cvGrabFrame(capture))
	{
		return false;
	}
	currentFrame++;
	frame=cvRetrieveFrame(capture);
	if(!frame)
	{
		return false;
	}
	return true;
}
void FrameCapture::Clear()
{
	cvReleaseCapture(&capture);
	capture=0;
}

