
#ifndef __SMART_RES_H_
#define __SMART_RES_H_


#include "cocos2d.h"

USING_NS_CC;

#define _center     SmartRes::sharedRes()->getCenter()
#define _top        SmartRes::sharedRes()->getTop()
#define _right      SmartRes::sharedRes()->getRight()
#define _bottom     SmartRes::sharedRes()->getBottom()
#define _left       SmartRes::sharedRes()->getLeft()
#define _scale      SmartRes::sharedRes()->getScale()
#define _xy(v)      SmartRes::sharedRes()->xy(v)

class CSmartRes
{
public:
    static CSmartRes* sharedRes(void);

    // 设定虚拟屏幕的宽度
    void setVirtualScreenWidth(float width);

    const CCSize getScreenSize(void) {
        return m_screenSize;
    }

    float getScale(void) {
        return m_scale;
    }

    const CCPoint getCenter(void) {
        return m_center;
    }

    float getTop(void) {
        return m_top;
    }

    float getRight(void) {
        return m_right;
    }

    float getBottom(void) {
        return m_bottom;
    }

    float getLeft(void) {
        return m_left;
    }

    float xy(float v) {
        return m_scale * v;
    }

private:
    CSmartRes(void)
    : m_scale(1.0f)
    , m_top(0)
    , m_right(0)
    , m_bottom(0)
    , m_left(0)
    {
    }
    bool init(void);

    static CSmartRes* s_sharedRes;

    CCSize m_screenSize;
    CCPoint m_center;
    float m_scale;
    float m_top;
    float m_right;
    float m_bottom;
    float m_left;
};

#endif __SMART_RES_H_