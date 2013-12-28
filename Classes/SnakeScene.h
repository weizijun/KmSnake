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
	//��ʼ�������߿�
	bool _InitBackgroundCell();

	//��ʼ��������
	bool _InitBackgroundLayer();

	//��ʼ��UI��
	bool _InitUILayer();

	//��ʼ������
	bool _InitFrog();

	//��ʼ����
	bool _InitSnake();

	bool _InitDiamond();

	bool _InitSuperDiamond();

	//��ʼ����Ϸ
	bool _InitGame();

	//��������
	void _PlayMunchSound();
	void _PlayGameOverSound();
	void _PlayBackgroundSound();

	//��Ϸѭ������
	void _GameCircle(float dt);

	//��������ص�����
	void _GameResetCallback(CCObject* pSender);

	//�����ͣ�ص�����
	void _GamePauseCallback(CCObject* pSender);

	//��������ص�����
	void _GameContinueCallback(CCObject* pSender);

private:
	//�������ܵ�λ��
	CCPoint _SetRandCell();

	void _SetFrogCell();	
	void _SetNormalDiamondCell();
	void _SetSuperDiamondCell();


	//������Ϸ
	void _GameOver();

	//��ͣ��Ϸ
	void _GamePause();

	//������Ϸ
	void _GameContinue();

	//�����߳Ե���Ʒ
	void _HandleEat();
	bool _HandleEatFrog(const CSnakeHead *);
	bool _HandleEatNormalDiamond(const CSnakeHead *);
	bool _HandleEatSuperDiamond(const CSnakeHead *);

	//����Ƿ�Ϊ˫��
	void _CheckDoubleCilck(float tt);

	//�ж�ǰ���ǲ��ǻ�����
	bool _CheckMoveToward();

	//8���ʯ�Զ���ʧ
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