#ifndef __SNAKE_H__
#define __SNAKE_H__

#include "SnakeHead.h"
#include "SnakeBody.h"

USING_NS_CC;

class CSnake : public CCNode
{
public:
	~CSnake();
	CSnake(int cellx, int celly);

	const Direction GetDirection() const { return m_Direction; }
	void SetDirection(const Direction direction);
	void InitDirection();

	CSnakeHead *GetHead() { return m_SnakeHead; }
    CCArray* GetTailArr() { return &m_ArrTail; }
	int GetTailLength() { return m_ArrTail.count(); }
	void Grow() { m_isGrow = true; }

	int GetNextX();
	int GetNextY();

	bool Move();

	void Reset(int cellx, int celly);


private:
	CSnakeHead *m_SnakeHead;
	Direction m_Direction;
	bool m_isGrow;
	Direction m_LastMoveDirection;
	CCArray m_ArrTail;
};

#endif