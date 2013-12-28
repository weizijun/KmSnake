#ifndef __SNAKE_SCENE_H__
#define __SNAKE_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Snake.h"
#include "Frog.h"
#include "NormalDiamond.h"
#include "SuperDiamond.h"

using namespace cocos2d;

enum Snake_Food
{
	Food_Frog = 1,
	Food_Normal_Diamond = 2,
	food_Super_Diamon = 3,
};

class CSnakeScene : public cocos2d::CCLayer
{
public:
	virtual bool init();

	static cocos2d::CCScene* scene();

	CREATE_FUNC(CSnakeScene);

	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void registerWithTouchDispatcher();

	bool _EraseDiamondVec(DiamondI * p_Diamond);
private:
	//初始化背景边框
	bool _InitBackgroundCell();

	//初始化背景层
	bool _InitBackgroundLayer();

	//初始化UI层
	bool _InitUILayer();

	//初始化青蛙
	bool _InitFrog();

	//初始化蛇
	bool _InitSnake();

	bool _InitDiamond();

	bool _InitSuperDiamond();

	//初始化游戏
	bool _InitGame();

	//播放音乐
	void _PlayMunchSound();
	void _PlayGameOverSound();
	void _PlayBackgroundSound();

	//游戏循环函数
	void _GameCircle(float dt);

	//点击重启回调函数
	void _GameResetCallback(CCObject* pSender);

	//点击暂停回调函数
	void _GamePauseCallback(CCObject* pSender);

	//点击继续回调函数
	void _GameContinueCallback(CCObject* pSender);

private:
	//设置青蛙的位置
	CCPoint _SetRandCell();

	void _SetFrogCell();	
	void _SetNormalDiamondCell();
	void _SetSuperDiamondCell();


	//结束游戏
	void _GameOver();

	//暂停游戏
	void _GamePause();

	//继续游戏
	void _GameContinue();

	//处理蛇吃到物品
	void _HandleEat();
	bool _HandleEatFrog(const CSnakeHead *);
	bool _HandleEatNormalDiamond(const CSnakeHead *);
	bool _HandleEatSuperDiamond(const CSnakeHead *);

	//检查是否为双击
	void _CheckDoubleCilck(float tt);

	//判断前移是不是会碰壁
	bool _CheckMoveToward();

	//8秒后宝石自动消失
	void _DiamondDisappear(float tt);

private:
	//int m_CellsHorizon;
	//int m_CellsVertical;
	//int m_CellsWidthBegin;
	//int m_CellsWidthEnd;
	//int m_CellsHeightBegin;
	//int m_CellsHeightEnd;
	bool m_IsDoubleClicked; 

	int m_nScore;
	int m_HighestScore;
	int m_EatFrogNum;
	int m_SuperDiamondTimes;
	bool m_IsGameRunning;
	CCSet *m_PauseAllTargets;

	CCLabelTTF* m_ScoreText;
	CCLabelTTF* m_HighestScoreText;
	CCLabelTTF* m_GameOverText;
	CCLabelTTF* m_BeginText;
	bool m_IsMenuShow;
	CCMenu *m_PauseMenu;
	CCSprite* m_PauseBackGround;

	CSnake *m_Snake;
	double m_SnakeFlame;
	CFrog *m_Frog;
	DiamondI *m_NormalDiamond;
	DiamondI *m_SuperDiamond;
	int m_FoodType;
	std::vector<DiamondI *> m_DiamondVec;
};

#endif