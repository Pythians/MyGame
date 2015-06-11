/*
* ResourcesManage.h
* Demo
* Used: Manage Resourse
*
* Create by K on 15/6/4
* Last change by K on 15/6/4
*/


#ifndef _BgLayer_H_
#define _BgLayer_H_

#include "Config.h"
#include "Layer/DrawSp.h"

class BgLayer : public cocos2d::Node
{

public:
	bool init( );

	static BgLayer * create( LineLayer * linelayer );
protected:
	BgLayer( LineLayer * linelayer);
	~BgLayer( );

private:
	LineLayer * _lineLayer;
};


#endif