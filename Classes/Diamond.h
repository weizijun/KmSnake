#ifndef __DIAMOND_H__
#define __DIAMOND_H__

#include "CellSpriteI.h"

class DiamondI : public CellSpriteI
{
public:
	DiamondI(){}


	void SetDesappear(CCLayer* layer,float tt);

private:
	void _Disappear(float tt);
	CCLayer* m_layer;
};

#endif