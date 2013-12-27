#include "cocos2d.h"
#include "SnakeHead.h"
#include "SnakeGlobal.h"

CSnakeHead::CSnakeHead(int cellX,int cellY)
{

	m_CellX = cellX;
	m_CellY = cellY;

	m_Animation = CCAnimation::create();
	CCImage *image = new CCImage();
	image->autorelease();
	image->initWithImageFile(SnakeGolbal::SNAKE_HEAD_IMAGE);
	CCTexture2D *texture = new CCTexture2D();
	texture->initWithImage(image);
	
	int col = 3;
	m_TileW = texture->getPixelsWide() / col;
	m_TileH = texture->getPixelsHigh();

	for (int i = 0; i < col; ++i)
	{
		m_Animation->addSpriteFrameWithTexture(texture, CCRectMake(i*m_TileW, 0, m_TileW, m_TileH));
	}

	CCSpriteFrame *frm = ((CCAnimationFrame*)(m_Animation->getFrames()->objectAtIndex(0)))->getSpriteFrame();

	this->initWithSpriteFrame(frm);

	this->SetCell(cellX,cellY);
}

void CSnakeHead::SetRotation(const Direction dirction)
{
	switch(dirction)
	{
	case UP :
		this->setRotation(180);
		break;
	case DOWN:
		this->setRotation(0);
		break;
	case LEFT:
		this->setRotation(90);
		break;
	case RIGHT:
		this->setRotation(270);
		break;
	}
}