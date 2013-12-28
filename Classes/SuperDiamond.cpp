#include "cocos2d.h"
#include "SuperDiamond.h"
#include "SnakeGlobal.h"

CSuperDiamond::CSuperDiamond(int cellX,int cellY)
{
	m_CellX = cellX;
	m_CellY = cellY;

	m_Animation = CCAnimation::create();
	CCImage *image = new CCImage();
	image->autorelease();
	image->initWithImageFile(SnakeGolbal::SUPER_DIAMOND_IMAGE);
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