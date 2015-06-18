/******************************************************************************
Copyright( c ) 2015 H·K

http://www.cnblogs.com/pythian

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files( the "Software" ), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************************/

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

