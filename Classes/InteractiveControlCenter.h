/*
* InteractiveControlCenter.h
* Demo
* Used: Manage touch key listener
*
* Create by K on 15/3
* Last change by K on 15/4/13
*/

#ifndef InteractiveControlCenter_H_
#define InteractiveControlCenter_H_

#include <cocos2d.h>
#include "Config.h"

USING_NS_CC;

class InteractiveControlCenter
	: public Layer
{
public:
	InteractiveControlCenter( );
	~InteractiveControlCenter( );

public:

	virtual bool init( );

	virtual bool onTouchBegan( cocos2d::Touch *touch, Event *unused_event );
	virtual void onTouchMoved( cocos2d::Touch *touch, Event *unused_event );
	virtual void onTouchEnded( cocos2d::Touch *touch, Event *unused_event );
	virtual void onTouchCancelled( cocos2d::Touch *touch, Event *unused_event );


	CREATE_FUNC( InteractiveControlCenter );
private:
	// 保存触摸点
	Vec2 _vec[ VECTSIZE ];
	// 显示触摸点
	DrawNode * _drawNode;
	// 触摸点颜色
	Color4F _color;

public:
	// 设置触摸点颜色 默认颜色 0.7透明的黑色
	void setColor( Color4F color = Color4F( 0, 0, 0, 0.7f ) );
};


#endif

