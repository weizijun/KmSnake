#ifndef __SNAKE_TAIL_PART_H__
#define __SNAKE_TAIL_PART_H__

#include "CellSpriteI.h"
#include "SnakeHead.h"

USING_NS_CC;

class CSnakeBody : public CellSpriteI
{
public:
	CSnakeBody(const CSnakeHead* head);
};

#endif