#include "cocos2d.h"
#include "NormalDiamond.h"
#include "SnakeGlobal.h"

CNormalDiamond::CNormalDiamond(int cellX,int cellY)
{	
	this->SetCell(cellX,cellY);
	this->initWithFile(SnakeGolbal::DIAMOND_IMAGE);
}