#include "cocos2d.h"
#include "SnakeBody.h"
#include "SnakeGlobal.h"

CSnakeBody::CSnakeBody(const CSnakeHead* head)
{
	this->SetCell(head->GetCellX(),head->GetCellY());
	this->initWithFile(SnakeGolbal::SNAKE_BODY_IMAGE);
}