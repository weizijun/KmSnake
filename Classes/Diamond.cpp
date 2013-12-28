#include "Diamond.h"
#include "cocos2d.h"

using namespace cocos2d;

void DiamondI::SetDesappear(CCLayer* layer,float tt)
{
	m_layer = layer;
	schedule(schedule_selector(DiamondI::_Disappear),tt);
}

void DiamondI::_Disappear(float tt)
{
	m_layer->removeChild(this);
}
