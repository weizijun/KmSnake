#ifndef __ICELL_ENTITY_H__
#define __ICELL_ENTITY_H__

#include "cocos2d.h"
#include "SnakeGlobal.h"

USING_NS_CC;

enum Direction
{
	DIR_NULL,
	UP = 1,
	DOWN,
	LEFT,
	RIGHT
};

static int AddtoX(const Direction direction, const int dx)
{
	switch(direction)
	{
	case UP:
	case DOWN:
		return dx;
	case LEFT:
		return dx - 1;
	case RIGHT:
		return dx + 1;
	}

	return dx;
}

static int AddtoY(const Direction direction, const int dy)
{
	switch(direction) 
	{
	case LEFT:
	case RIGHT:
		return dy;
	case UP:
		return dy + 1;
	case DOWN:
		return dy - 1;
	}

	return dy;
}


static Direction Opposite(const Direction direction)
{
	switch(direction) {
	case UP:
		return DOWN;
	case DOWN:
		return UP;
	case LEFT:
		return RIGHT;
	case RIGHT:
		return LEFT;
	default:
		return DIR_NULL;
	}
}


class CellSpriteI : public CCSprite
{
public:
	CellSpriteI();

	virtual const int GetCellX() const;
	virtual const int GetCellY() const;

	virtual void SetCell(const CellSpriteI& cell);
	virtual void SetCell(const int cellX,const int cellY);

	virtual bool IsInSameCell(const CellSpriteI& cell) const;

	virtual void Animate(const float interval);

protected:
	int m_CellX;
	int m_CellY;

	int m_TileW;
	int m_TileH;

	CCRepeatForever *m_Ani;
	CCAnimation *m_Animation;
};

#endif