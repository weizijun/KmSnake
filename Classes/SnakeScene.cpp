#include "SnakeScene.h"
#include "SnakeGlobal.h"
#include "SmartRes.h"
#include "CCScheduler.h"
#include "SnakeBody.h"

using namespace cocos2d;

CCScene* CSnakeScene::scene()
{
	CCScene *t_Scene = NULL;
	do 
	{
		t_Scene = CCScene::create();
		CC_BREAK_IF(!t_Scene);

		CSnakeScene *layer = CSnakeScene::create();
		CC_BREAK_IF(!layer);

		layer->setTouchEnabled(true);

		t_Scene->addChild(layer);
	} while (false);

	return t_Scene;
}

bool CSnakeScene::init()
{
	bool t_Ret = false;
	do 
	{
		//创建4层layer
		for (int i = 0; i < SnakeGolbal::LAYER_COUNT; ++i)
		{
			this->addChild(CCLayer::create());
		}

		//初始化背景层
		CC_BREAK_IF(!_InitBackgroundLayer());

		//初始化背景边框
		CC_BREAK_IF(!_InitBackgroundCell());

		//初始化UI层
		CC_BREAK_IF(!_InitUILayer());

		//初始化青蛙
		CC_BREAK_IF(!_InitFrog());

		//初始化蛇
		CC_BREAK_IF(!_InitSnake());

		CC_BREAK_IF(!_InitDiamond());

		CC_BREAK_IF(!_InitSuperDiamond());

		//初始化游戏
		CC_BREAK_IF(!_InitGame());

		t_Ret = true;
	} while (false);
	return t_Ret;
}

bool CSnakeScene::_InitBackgroundCell()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	//int t_WidthCells = static_cast<int>(SmartRes::sharedRes()->getRight() / SnakeGolbal::CELL_WIDTH);
	
	SnakeGolbal::g_CellsWidthEnd = static_cast<int>(CSmartRes::sharedRes()->getRight() - 10);
	SnakeGolbal::g_CellsWidthBegin = (SnakeGolbal::g_CellsWidthEnd - 100) % SnakeGolbal::CELL_WIDTH + 100;	

	SnakeGolbal::g_CellsHeightEnd = static_cast<int>(CSmartRes::sharedRes()->getTop() - 10);
	SnakeGolbal::g_CellsHeightBegin = (SnakeGolbal::g_CellsHeightEnd - 10) % SnakeGolbal::CELL_HEIGHT + 10;

	SnakeGolbal::g_CellsHorizon = (SnakeGolbal::g_CellsWidthEnd - SnakeGolbal::g_CellsHeightBegin) / SnakeGolbal::CELL_WIDTH;
	SnakeGolbal::g_CellsVertical = (SnakeGolbal::g_CellsHeightEnd - SnakeGolbal::g_CellsHeightBegin) / SnakeGolbal::CELL_HEIGHT;

	CCLayer* layer = (CCLayer*)this->getChildren()->objectAtIndex(SnakeGolbal::LAYER_BACKGROUND);

	CCSprite* t_BackgroupLineWidthBegin = CCSprite::create(SnakeGolbal::BACKGROUND_LINE_WIDTH_IMAGE);
	if(!t_BackgroupLineWidthBegin)
	{
		return false;
	}	
	
	t_BackgroupLineWidthBegin->setAnchorPoint(ccp(0,1));
	float scaleX = (SnakeGolbal::g_CellsWidthEnd - SnakeGolbal::g_CellsWidthBegin) / t_BackgroupLineWidthBegin->getContentSize().width;
	t_BackgroupLineWidthBegin->setScaleX(scaleX);
	t_BackgroupLineWidthBegin->setPosition(ccp(SnakeGolbal::g_CellsWidthBegin,SnakeGolbal::g_CellsHeightBegin));
	
	layer->addChild(t_BackgroupLineWidthBegin);

	CCSprite* t_BackgroupLineWidthEnd = CCSprite::create(SnakeGolbal::BACKGROUND_LINE_WIDTH_IMAGE);
	if(!t_BackgroupLineWidthEnd)
	{
		return false;
	}	

	t_BackgroupLineWidthEnd->setAnchorPoint(ccp(0,0));
	t_BackgroupLineWidthEnd->setScaleX(scaleX);
	t_BackgroupLineWidthEnd->setPosition(ccp(SnakeGolbal::g_CellsWidthBegin,SnakeGolbal::g_CellsHeightEnd));

	layer->addChild(t_BackgroupLineWidthEnd);

	CCSprite* t_BackgroupLineHeightBegin = CCSprite::create(SnakeGolbal::BACKGROUND_LINE_HEIGHT_IMAGE);
	if(!t_BackgroupLineHeightBegin)
	{
		return false;
	}	

	float scaleY = (SnakeGolbal::g_CellsHeightEnd - SnakeGolbal::g_CellsHeightBegin) / t_BackgroupLineHeightBegin->getContentSize().height;
	t_BackgroupLineHeightBegin->setAnchorPoint(ccp(1,0));
	t_BackgroupLineHeightBegin->setScaleY(scaleY);
	t_BackgroupLineHeightBegin->setPosition(ccp(SnakeGolbal::g_CellsWidthBegin,SnakeGolbal::g_CellsHeightBegin));
	layer->addChild(t_BackgroupLineHeightBegin);

	CCSprite* t_BackgroupLineHeightEnd = CCSprite::create(SnakeGolbal::BACKGROUND_LINE_HEIGHT_IMAGE);
	if(!t_BackgroupLineHeightEnd)
	{
		return false;
	}	

	t_BackgroupLineHeightEnd->setAnchorPoint(ccp(0,0));
	t_BackgroupLineHeightEnd->setScaleY(scaleY);
	t_BackgroupLineHeightEnd->setPosition(ccp(SnakeGolbal::g_CellsWidthEnd,SnakeGolbal::g_CellsHeightBegin));

	layer->addChild(t_BackgroupLineHeightEnd);


	return true;
}

bool CSnakeScene::_InitBackgroundLayer()
{
	CCLayer* layer = (CCLayer*)this->getChildren()->objectAtIndex(SnakeGolbal::LAYER_BACKGROUND);
	layer->setTouchEnabled(true);

	CCSprite* pSprite = CCSprite::create(SnakeGolbal::BACKGROUND_IMAGE);
	if(!pSprite)
	{
		return false;
	}
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	pSprite->setPosition(ccp(size.width/2,size.height/2));
	layer->addChild(pSprite);

	//CCSprite* t_BackgroupLineSprite = CCSprite::create(SnakeGolbal::BACKGROUND_LINE_IMAGE);
	//if(!t_BackgroupLineSprite)
	//{
	//	return false;
	//}
	//float scalY=size.height/t_BackgroupLineSprite->getContentSize().height;//设置y轴方向的缩放系数
	//t_BackgroupLineSprite->setScaleY(scalY);
	//t_BackgroupLineSprite->setPosition(ccp(size.width/2,size.height/2));
	//layer->addChild(t_BackgroupLineSprite);

	return true;
}

//初始化UI层
bool CSnakeScene::_InitUILayer()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCLayer* layer = (CCLayer*)this->getChildren()->objectAtIndex(SnakeGolbal::LAYER_UI);
	//CCMenuItemImage *pResetItem = CCMenuItemImage::create(
	//	SnakeGolbal::RESET_IMAGE,
	//	SnakeGolbal::RESET_IMAGE,
	//	this,
	//	menu_selector(SnakeScene::GameResetCallback));

	//CC_BREAK_IF(!pResetItem);		
	//pResetItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width-30,30));

	CCMenuItemImage *t_PauseItem = CCMenuItemImage::create(
		SnakeGolbal::PAUSE_ITEM_IMAGE,
		SnakeGolbal::PAUSE_ITEM_IMAGE,
		this,
		menu_selector(CSnakeScene::_GamePauseCallback));
	if(!t_PauseItem)
	{
		return false;
	}
	t_PauseItem->setPosition(CCDirector::sharedDirector()->getWinSize().width-30,CCDirector::sharedDirector()->getWinSize().height-30);

	CCMenu* pMenu = CCMenu::create(t_PauseItem, NULL);
	pMenu->setPosition(CCPointZero);
	if(! pMenu)
	{
		return false;
	}
	layer->addChild(pMenu);


	m_nScore = 0;
	char t_Score[128] = {0};
	sprintf(t_Score, "Score: %d", m_nScore);
	m_ScoreText = CCLabelTTF::create(t_Score,SnakeGolbal::SCORE_TTF,SnakeGolbal::SCORE_SIZE);
	m_ScoreText->setPosition(ccp(30,size.height - 30));
	//m_ScoreText->setAnchorPoint(ccp(0,0.5));
	layer->addChild(m_ScoreText);

	m_HighestScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("highest_score");
	char t_HighestScore[128] = {0};
	sprintf(t_HighestScore, "HighestScore: %d", m_HighestScore);
	m_HighestScoreText = CCLabelTTF::create(t_HighestScore,SnakeGolbal::SCORE_TTF,SnakeGolbal::HIGHEST_SCORE_SIZE);
	m_HighestScoreText->setPosition(ccp(30,size.height - 60));
	//m_HighestScoreText->setAnchorPoint(ccp(0,0.5));
	layer->addChild(m_HighestScoreText);

	m_BeginText = CCLabelTTF::create("Snake On Phone!",SnakeGolbal::BEGIN_TTF,SnakeGolbal::BEGIN_SIZE);
	m_BeginText->setPosition(ccp(size.width/2,size.height/2));
	layer->addChild(m_BeginText);
	m_BeginText->setScale(0.0f);

	m_GameOverText = new CCLabelTTF();
	m_GameOverText->initWithString("Game Over!",SnakeGolbal::GAMEOVER_TTF,SnakeGolbal::GAMEOVER_SIZE);
	m_GameOverText->setPosition(ccp(size.width/2,size.height/2));
	m_GameOverText->retain();
	m_GameOverText->autorelease();

	return true;
}

//初始化青蛙
bool CSnakeScene::_InitFrog()
{
	m_Frog = new CFrog(0,0);	
	m_Frog->Animate(0.5f);
	CCLayer* layer = (CCLayer*)this->getChildren()->objectAtIndex(SnakeGolbal::LAYER_FOOD);
	layer->addChild(m_Frog);

	return true;
}

//初始化蛇
bool CSnakeScene::_InitSnake()
{
	m_Snake = new CSnake(0,SnakeGolbal::g_CellsVertical/2);
	m_Snake->autorelease();		
	m_Snake->GetHead()->Animate(0.5f);
	m_Snake->Grow();
	CCLayer*layer = (CCLayer*)this->getChildren()->objectAtIndex(SnakeGolbal::LAYER_SNAKE);
	layer->addChild(m_Snake);

	return true;
}

bool CSnakeScene::_InitDiamond()
{
	m_NormalDiamond = new CNormalDiamond(0,0);
	//m_Diamond->autorelease();
	return true;
}

bool CSnakeScene::_InitSuperDiamond()
{
	m_SuperDiamond = new CSuperDiamond(0,0);
	//m_SuperDiamond->autorelease();
	m_SuperDiamond->Animate(0.5f);

	return true;
}

bool CSnakeScene::_InitGame()
{
	//隐藏菜单
	m_IsMenuShow = false;

	//双击标识
	m_IsDoubleClicked = false;

	//设置随机数种子
	srand(time(NULL));

	//摆放青蛙位置
	_SetFrogCell();
	m_EatFrogNum = 0;
	m_SuperDiamondTimes = 0;

	m_FoodType = 1;

	//蛇出洞
	m_Snake->Grow();

	//设置蛇移动频率
	m_SnakeFlame = 0.5;
	schedule(schedule_selector(CSnakeScene::_GameCircle),m_SnakeFlame);

	//开始游戏
	m_IsGameRunning = true;

	return true;
}

CCPoint CSnakeScene::_SetRandCell()
{
	//获得所有非蛇所在位置的空格，放入容器
	std::vector<CCPoint> t_CellPointVec;
	for (int i = 1; i<SnakeGolbal::g_CellsHorizon-1; ++i)
	{
		for (int j = 1; j<SnakeGolbal::g_CellsVertical-1; ++j)
		{
			if (i == m_Snake->GetHead()->GetCellX() && j == m_Snake->GetHead()->GetCellY())
			{
				continue;
			}

			CCArray *t_TailArr = m_Snake->GetTailArr();
			bool t_TailFlag = false;
			for(int it = t_TailArr->count() - 1; it >= 0; --it)
			{
				CSnakeBody *t_TailEnd = (CSnakeBody *)(t_TailArr->objectAtIndex(it));
				if (t_TailEnd->GetCellX() == i && t_TailEnd->GetCellY() == j)
				{
					t_TailFlag = true;
					//delete t_TailEnd;
					break;
				}
				else
				{
					//delete t_TailEnd;
				}
			}

			if (t_TailFlag == true)
			{
				continue;
			}

			t_CellPointVec.push_back(ccp(i,j));
		}
	}

	//从容器中随机取出一个格子
	int t_RandCell = CCRANDOM_0_1() * (t_CellPointVec.size()-1);
	int t_RandCellX = t_CellPointVec[t_RandCell].x;
	int t_RandCellY = t_CellPointVec[t_RandCell].y;

	return ccp(t_RandCellX,t_RandCellY);
}

void CSnakeScene::_SetFrogCell()
{
	CCPoint t_Pos = _SetRandCell();
	m_Frog->SetCell(t_Pos.x,t_Pos.y);
}

void CSnakeScene::_SetNormalDiamondCell()
{
	CCPoint t_Pos = _SetRandCell();
	m_NormalDiamond->SetCell(t_Pos.x,t_Pos.y);
}
void CSnakeScene::_SetSuperDiamondCell()
{
	CCPoint t_Pos = _SetRandCell();
	m_SuperDiamond->SetCell(t_Pos.x,t_Pos.y);
}

//void CSnakeScene::_SetDiamondCell()
//{
//	CCPoint t_CellPoint = _SetDiamondCellBase();
//	m_Diamond->SetCell(t_CellPoint.x,t_CellPoint.y);
//}
//
//void CSnakeScene::_SetSuperDiamondCell()
//{
//	CCPoint t_CellPoint = _SetDiamondCellBase();
//	m_SuperDiamond->SetCell(t_CellPoint.x,t_CellPoint.y);
//}

void CSnakeScene::_GameCircle(float dt)
{
	//CCLOG("circle:%f,time:%d",dt,time(NULL));
	CSnakeHead * t_SnakeHead = m_Snake->GetHead();
	CCLOG("x:%d,y:%d",t_SnakeHead->GetCellX(),t_SnakeHead->GetCellY());
	
	if (m_IsGameRunning)
	{
		//判断前移是不是会碰壁
		bool t_GameOverFlag = _CheckMoveToward();
		if (t_GameOverFlag == true)
		{			
			_GameOver();
			return;
		}

		//往前移动一个
		if (!m_Snake->Move())
		{
			_GameOver();
			return;
		}

		//吃东西
		_HandleEat();
	}
}

bool CSnakeScene::_CheckMoveToward()
{
	const CSnakeHead *t_SnakeHead = m_Snake->GetHead();
	const Direction t_Direction = m_Snake->GetDirection();
	bool t_GameOverFlag = false;
	switch(t_Direction)
	{
	case UP:
		if (t_SnakeHead->GetCellY() >= SnakeGolbal::g_CellsVertical-1)
		{
			t_GameOverFlag = true;
		}
		break;
	case DOWN:
		if (t_SnakeHead->GetCellY() <= 0)
		{
			t_GameOverFlag = true;
		}
		break;
	case LEFT:
		if (t_SnakeHead->GetCellX() <= 0)
		{
			t_GameOverFlag = true;
		}
		break;
	case RIGHT:
		if (t_SnakeHead->GetCellX() >= SnakeGolbal::g_CellsHorizon-2)			
		{
			t_GameOverFlag = true;
		}
		break;
	}

	return t_GameOverFlag;
}

void CSnakeScene::_GameResetCallback(CCObject* pSender)
{
	//蛇从初始位置重新进入
	m_Snake->Reset(0,SnakeGolbal::g_CellsVertical/2);
	//分数清零
	m_nScore = 0;
	m_ScoreText->setString("Score: 0");
	CCLayer *layer = (CCLayer*)this->getChildren()->objectAtIndex(SnakeGolbal::LAYER_UI);	
	
	m_EatFrogNum = 0;
	
	m_FoodType = Food_Frog;

	m_SuperDiamondTimes = 0;

	//如果游戏进行中重启
	if (m_IsGameRunning == true)
	{
		//保存最高分
		CCUserDefault::sharedUserDefault()->setIntegerForKey("highest_score",m_HighestScore);
	}
	//如果死亡后的继续
	else
	{
		//移除结束游戏提示
		layer->removeChild(m_GameOverText);

		//开始游戏
		m_IsGameRunning = true;
	}

	//重新设置蛇移动的速度
	m_SnakeFlame = 0.5;
    unschedule(schedule_selector(CSnakeScene::_GameCircle));
    schedule(schedule_selector(CSnakeScene::_GameCircle),m_SnakeFlame);
    
	//恢复游戏
	CCDirector::sharedDirector()->resume();
	//CCDirector::sharedDirector()->getScheduler()->resumeTargets(m_PauseAllTargets);
	//CC_SAFE_RELEASE_NULL(m_PauseAllTargets);

	//隐藏菜单栏
	layer->removeChild(m_PauseMenu);
	layer->removeChild(m_PauseBackGround);
	m_IsMenuShow = false;
}

void CSnakeScene::_GameContinueCallback(CCObject* pSender)
{
	_GameContinue();
}

void CSnakeScene::_GamePauseCallback(CCObject* pSender)
{
	_GamePause();
}

void CSnakeScene::_GamePause()
{
	if (m_IsMenuShow == false)
	{

		do 
		{
			//暂停
			CCDirector::sharedDirector()->pause();
			//m_PauseAllTargets = CCDirector::sharedDirector()->getScheduler()->pauseAllTargets();
			//CC_SAFE_RETAIN(m_PauseAllTargets);

			CCSize size = CCDirector::sharedDirector()->getWinSize();
			CCLayer *layer = (CCLayer*)this->getChildren()->objectAtIndex(SnakeGolbal::LAYER_UI);	


			m_PauseBackGround = CCSprite::create(SnakeGolbal::PAUSE_MENU_IMAGE);
			CC_BREAK_IF(!m_PauseBackGround);
			m_PauseBackGround->setPosition(ccp(size.width/2,size.height/2));
			layer->addChild(m_PauseBackGround);

			CCMenuItemImage *t_MenuItemContinue = CCMenuItemImage::create(
				SnakeGolbal::IN_MENU_CONTINUE_IMAGE,
				SnakeGolbal::IN_MENU_CONTINUE_IMAGE,
				this,
				menu_selector(CSnakeScene::_GameContinueCallback));
			CC_BREAK_IF(!t_MenuItemContinue);
			t_MenuItemContinue->setPosition(ccp(10,10));

			CCMenuItemImage *t_MenuItemReset = CCMenuItemImage::create(
				SnakeGolbal::IN_MENU_RESET_IMAGE,
				SnakeGolbal::IN_MENU_RESET_IMAGE,
				this,
				menu_selector(CSnakeScene::_GameResetCallback));
			CC_BREAK_IF(!t_MenuItemReset);
			t_MenuItemReset->setPosition(ccp(20,20));



			m_PauseMenu = CCMenu::create(t_MenuItemContinue,t_MenuItemReset,NULL);
			CC_BREAK_IF(!m_PauseMenu);
			m_PauseMenu->setPosition(ccp(size.width/2,size.height/2));
			m_PauseMenu->alignItemsVertically();
			layer->addChild(m_PauseMenu);

			m_IsMenuShow = true;
		} while (false);
	}
	else
	{
		//_GameContinue();	
		m_IsMenuShow = false;
	}
}



void CSnakeScene::_GameContinue()
{
	do 
	{
		//恢复
		CCDirector::sharedDirector()->resume();
		//CCDirector::sharedDirector()->getScheduler()->resumeTargets(m_PauseAllTargets);
		//CC_SAFE_RELEASE_NULL(m_PauseAllTargets);

		//隐藏菜单栏
		CCLayer *layer = (CCLayer*)this->getChildren()->objectAtIndex(SnakeGolbal::LAYER_UI);	
		layer->removeChild(m_PauseMenu);
		layer->removeChild(m_PauseBackGround);		
		m_IsMenuShow = false;
	} while (false);
}

void CSnakeScene::_GameOver()
{
	_PlayGameOverSound();
	CCLayer *layer = (CCLayer*)this->getChildren()->objectAtIndex(SnakeGolbal::LAYER_UI);
	layer->addChild(m_GameOverText);
	m_GameOverText->setScale(0);
	m_GameOverText->runAction(CCScaleTo::create(1.0,1.0));
	m_GameOverText->runAction(CCRotateBy::create(1.0,360));

	m_IsGameRunning = false;
	CCUserDefault::sharedUserDefault()->setIntegerForKey("highest_score",m_HighestScore);

	_GamePause();
}

void CSnakeScene::_HandleEat()
{
	const CSnakeHead *t_SnakeHead = m_Snake->GetHead();

	bool t_IsEatFood = false;
	switch (m_FoodType)
	{
	case Food_Frog:
		t_IsEatFood = _HandleEatFrog(t_SnakeHead);
		break;
	case Food_Normal_Diamond:
		t_IsEatFood = _HandleEatNormalDiamond(t_SnakeHead);
		break;
	case food_Super_Diamon:
		t_IsEatFood = _HandleEatSuperDiamond(t_SnakeHead);
		break;
	}

	if (true == t_IsEatFood)
	{
		//蛇长大一节
		m_Snake->Grow();

		int t_TailLength = m_Snake->GetTailLength();
		if (t_TailLength % 10 == 0)
		{
			if (m_SnakeFlame > 0.2)
			{
				m_SnakeFlame -= 0.1;
				unschedule(schedule_selector(CSnakeScene::_GameCircle));
				schedule(schedule_selector(CSnakeScene::_GameCircle),m_SnakeFlame);
			}			
		}

		CCLayer* layer = (CCLayer*)this->getChildren()->objectAtIndex(SnakeGolbal::LAYER_FOOD);
		switch (m_FoodType)
		{
		case Food_Frog:			
			//每吃到4个青蛙，钻石出现
			if (m_EatFrogNum != 0 && m_EatFrogNum % 2 == 0)
			{
				int t_Rand = CCRANDOM_0_1() * 999;
				bool t_SuperFlag = false;
				if (m_SuperDiamondTimes == 0)
				{
					
					if (t_Rand < 1000 * SnakeGolbal::FIRST_DIAMOND_RATE)
					{
						t_SuperFlag = true;
					}
				} 
				else if (m_SuperDiamondTimes == 1)
				{
					if (t_Rand < 1000 * SnakeGolbal::SECOND_DIAMOND_RATE)
					{
						t_SuperFlag = true;
					}
				}

				if (t_SuperFlag == true)
				{
					layer->removeChild(m_Frog);
					layer->addChild(m_SuperDiamond);	
					_SetSuperDiamondCell();
					m_FoodType = food_Super_Diamon;
				}
				else
				{
					layer->removeChild(m_Frog);
					layer->addChild(m_NormalDiamond);	
					_SetNormalDiamondCell();
					m_FoodType = Food_Normal_Diamond;
				}				
			}	
			break;
		case Food_Normal_Diamond:
		case food_Super_Diamon:
			layer->removeChild(m_NormalDiamond);
			layer->addChild(m_Frog);
			_SetFrogCell();
			m_FoodType = Food_Frog;		
			break;
		}


	}
}

bool CSnakeScene::_HandleEatFrog(const CSnakeHead *p_SnakeHead)
{
	if(p_SnakeHead->IsInSameCell(*m_Frog))
	{
		m_nScore += 50;
		char score[128] = {0};
		sprintf(score, "Score: %d", m_nScore);
		m_ScoreText->setString(score);

		if (m_nScore > m_HighestScore)
		{
			m_HighestScore = m_nScore;
			char highest_score[128] = {0};
			sprintf(highest_score, "HighestScore: %d", m_HighestScore);
			m_HighestScoreText->setString(highest_score);
		}

		//吃到青蛙的数量加1
		m_EatFrogNum++;	

		//青蛙位置随机摆放
		_SetFrogCell();

		//播放吃青蛙音效
		_PlayMunchSound();

		return true;
	}
	else
	{
		return false;
	}
}

bool CSnakeScene::_HandleEatNormalDiamond(const CSnakeHead *p_SnakeHead)
{
	if(p_SnakeHead->IsInSameCell(*m_NormalDiamond))
	{
		m_nScore += 100;
		char score[128] = {0};
		sprintf(score, "Score: %d", m_nScore);
		m_ScoreText->setString(score);

		if (m_nScore > m_HighestScore)
		{
			m_HighestScore = m_nScore;
			char highest_score[128] = {0};
			sprintf(highest_score, "HighestScore: %d", m_HighestScore);
			m_HighestScoreText->setString(highest_score);
		}

		//播放音效
		_PlayMunchSound();

		return true;
	}
	else
	{
		return false;
	}

}

bool CSnakeScene::_HandleEatSuperDiamond(const CSnakeHead *p_SnakeHead)
{
	if(p_SnakeHead->IsInSameCell(*m_SuperDiamond))
	{
		m_nScore += 150;
		char score[128] = {0};
		sprintf(score, "Score: %d", m_nScore);
		m_ScoreText->setString(score);

		if (m_nScore > m_HighestScore)
		{
			m_HighestScore = m_nScore;
			char highest_score[128] = {0};
			sprintf(highest_score, "HighestScore: %d", m_HighestScore);
			m_HighestScoreText->setString(highest_score);
		}

		//播放音效
		_PlayMunchSound();

		return true;
	}
	else
	{
		return false;
	}
}

bool CSnakeScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (m_IsDoubleClicked) {  
		m_IsDoubleClicked = false;  
		CCLog("double click");  
	}  
	else  
	{  
		//延时0.25s执行（注意在这0.25s的延时过程中clicked已经为true），  
		//如果在这个过程中再次click，那么就执行上面的双击事件处理了  
		//否则，那么就执行下面的回调函数了，处理单击事件  
		scheduleOnce(schedule_selector(CSnakeScene::_CheckDoubleCilck), 0.25f);  
		m_IsDoubleClicked = true;  
	}  

	return true;
}

void CSnakeScene::_CheckDoubleCilck(float tt)  
{  
	if (m_IsDoubleClicked) {  
		m_IsDoubleClicked = false;  
		CCLog("single click");  
	}  
} 

void CSnakeScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{

}

void CSnakeScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCLOG("ccTouchEnded");
    if (m_IsGameRunning == true)
    {
        CCPoint t_BeginPos = pTouch->getStartLocation();
        CCPoint t_EndPos = pTouch->getLocation();
        
        CCLOG("start x:%f,y%f",t_BeginPos.x,t_BeginPos.y);
        CCLOG("end x:%f,y%f",t_EndPos.x,t_EndPos.y);
        Direction t_Direction = m_Snake->GetDirection();
        float t_XLen;
        float t_YLen;
        float t_TanDirection;
        switch(t_Direction)
        {
            case UP:
            case DOWN:
                t_XLen = t_EndPos.x - t_BeginPos.x;
                t_YLen = t_EndPos.y - t_BeginPos.y;
                
                if (abs(t_XLen) < SnakeGolbal::LEAST_MOVE && abs(t_YLen) < SnakeGolbal::LEAST_MOVE)
                {
                    break;
                }
                
                t_TanDirection = t_XLen/t_YLen;
                
                if (t_TanDirection >= SnakeGolbal::LEAST_TAN_DIRECTION || t_TanDirection <= -SnakeGolbal::LEAST_TAN_DIRECTION)
                {
                    if (t_XLen > 0)
                    {
                        m_Snake->SetDirection(RIGHT);
                    }
                    else
                    {
                        m_Snake->SetDirection(LEFT);
                    }
                }
                else if ((t_XLen > 0 && t_Direction == UP) || (t_XLen < 0 && t_Direction == DOWN))
                {
                    double t_Rand = 0.1;
                    _GameCircle(t_Rand);
                }
                break;
            case LEFT:
            case RIGHT:
                t_XLen = t_EndPos.x - t_BeginPos.x;
                t_YLen = t_EndPos.y - t_BeginPos.y;
                
                if (abs(t_XLen) < 1 && abs(t_YLen) < 1)
                {
                    break;
                }
                
                t_TanDirection = t_YLen/t_XLen;
                
                if (t_TanDirection >= SnakeGolbal::LEAST_TAN_DIRECTION || t_TanDirection <= -SnakeGolbal::LEAST_TAN_DIRECTION)
                {
                    if (t_YLen > 0)
                    {
                        m_Snake->SetDirection(UP);
                    }
                    else
                    {
                        m_Snake->SetDirection(DOWN);
                    }
                }
                else if ((t_XLen > 0 && t_Direction == RIGHT) || (t_XLen < 0 && t_Direction == LEFT))
                {
                    double t_Rand = 0.1;
                    _GameCircle(t_Rand);		
                }
        }
    }
}
void CSnakeScene::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
	CCLOG("ccTouchCancelled");
}

void CSnakeScene::registerWithTouchDispatcher() 
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void CSnakeScene::_PlayMunchSound()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("munch.ogg");
}

void CSnakeScene::_PlayGameOverSound()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("game_over.ogg");
}

void CSnakeScene::_PlayBackgroundSound()
{

}

bool CSnakeScene::_EraseDiamondVec(DiamondI * p_Diamond)
{
	for (std::vector<DiamondI *>::iterator it = m_DiamondVec.begin(); it != m_DiamondVec.end(); ++it)
	{
		if ((*it)->GetCellX() == p_Diamond->GetCellX() && (*it)->GetCellY() == p_Diamond->GetCellY())
		{
			m_DiamondVec.erase(it);
			return true;
		}
	}

	return false;
}