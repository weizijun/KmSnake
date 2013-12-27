#ifndef __snake_head_h__
#define __snake_head_h__

#include "CellSpriteI.h"

USING_NS_CC;

class CSnakeHead : public CellSpriteI
{
public:
	CSnakeHead(int cellx,int celly);
	void SetRotation(const Direction direction);
};

#endif