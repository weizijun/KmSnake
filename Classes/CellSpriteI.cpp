#include "CellSpriteI.h"

const int CellSpriteI::GetCellX() const
{
	return m_CellX;
}

const int CellSpriteI::GetCellY() const
{
	return m_CellY;
}

void CellSpriteI::SetCell(const CellSpriteI& cell)
{
	return this->SetCell(cell.GetCellX(),cell.GetCellY());
}

void CellSpriteI::SetCell(const int cellX,const int cellY)
{
	this->m_CellX = cellX;
	this->m_CellY = cellY;

	this->setPosition(ccp(m_CellX*SnakeGolbal::CELL_WIDTH+SnakeGolbal::CELL_WIDTH/2+SnakeGolbal::g_CellsWidthBegin,m_CellY*SnakeGolbal::CELL_HEIGHT+SnakeGolbal::CELL_HEIGHT/2+SnakeGolbal::g_CellsHeightBegin));
}

bool CellSpriteI::IsInSameCell(const CellSpriteI& cell) const
{
	return m_CellX == cell.GetCellX() && m_CellY == cell.GetCellY();
}

void CellSpriteI::Animate(const float interval)
{
	m_Animation->setDelayPerUnit(interval);
	m_Ani = CCRepeatForever::create(CCAnimate::create(m_Animation));
	this->runAction(m_Ani);
}