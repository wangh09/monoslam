#pragma once
#include "Paras.h"
#include "FrameCapture.h"
#include "FrameCache.h"
class FrameHandler
{
public:
	FrameHandler(void);
	~FrameHandler(void);
	FrameCapture m_Capture;
};