#include "FeatureTracker.h"

FeatureTracker::FeatureTracker(void)
{
	m_tracker = 0;
}
FeatureTracker::~FeatureTracker(void)
{
}
void FeatureTracker::InitialTracker(TRACKERTYPE m_trackertype,int iwidth,int iheight)
{
	if(m_tracker)delete m_tracker;
	switch(m_trackertype)
	{
	case ZENAN_TRACKER:
		m_tracker = new ZeNanTracker();
	}
	m_tracker->iHeight = iheight;
	m_tracker->iWidth = iwidth;
}
TrackInfo* FeatureTracker::Track(TrackGraph* _Cache,int Frame_Ref,int Frame_)
{
	return m_tracker->Track(_Cache,Frame_Ref,Frame_);
}