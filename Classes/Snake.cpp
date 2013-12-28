#include "cocos2d.h"
#include "Snake.h"


CSnake::CSnake( int cellx, int celly)
{
	m_SnakeHead = new CSnakeHead(cellx,celly);
	m_SnakeHead->autorelease();
	InitDirection();
	this->addChild(m_SnakeHead);
	
}

void CSnake::SetDirection(const Direction direction)
{
	if (m_LastMoveDirection != Opposite(direction))
	{
		m_Direction = direction;
		m_SnakeHead->SetRotation(direction);
	}

	//m_Direction = direction;
	//m_SnakeHead->SetRotation(direction);
}

void CSnake::InitDirection()
{
	m_Direction = RIGHT;
	m_SnakeHead->SetRotation(m_Direction);
}

CSnake::~CSnake()
{

}

int CSnake::GetNextX()
{
	return AddtoX(m_Direction,m_SnakeHead->GetCellX());
}

int CSnake::GetNextY()
{
	return AddtoY(m_Direction,m_SnakeHead->GetCellY());
}

bool CSnake::Move()
{
	m_LastMoveDirection = m_Direction;
	if (m_isGrow)
	{
		m_isGrow = false;
		CSnakeBody *t_NewTailPart = new CSnakeBody(m_SnakeHead);
		this->addChild(t_NewTailPart);
		m_ArrTail.insertObject(t_NewTailPart,0);
	}
	else
	{
		if (m_ArrTail.count() > 0)
		{
			CSnakeBody *t_TailEnd = (CSnakeBody *)m_ArrTail.lastObject();
			m_ArrTail.removeLastObject(false);
			t_TailEnd->SetCell(*m_SnakeHead);

			m_ArrTail.insertObject(t_TailEnd,0);
		}		
	}

	m_SnakeHead->SetCell(GetNextX(),GetNextY());

	return true;
}

void CSnake::Reset(int cellx, int celly)
{
	InitDirection();

	m_SnakeHead->SetCell(cellx,celly);
	//m_ArrTail.removeAllObjects();

	for (int i = m_ArrTail.count() - 1; i >= 0; --i)
	{
		CSnakeBody *t_TailEnd = (CSnakeBody *)m_ArrTail.objectAtIndex(i);
		this->removeChild(t_TailEnd);
		m_ArrTail.removeObjectAtIndex(i);
	}

	Grow();
}