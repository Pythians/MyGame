/*
* GameScene.h
* Demo
* Used: Game Scene
* 
* Create by K on 15/4/5
* Last change by K on 15/4/13
*/

#ifndef _GameScene_H_
#define _GameScene_H_

#include "ManageConter.h"

class GameScene : public Layer
{
public:

	virtual bool init( );
	//void onEnter( ) ;
	//virtual void onExit( );

	static Scene * createScene( );
	CREATE_FUNC( GameScene );

private:
	// 管理中心
	ManageConter * _manageConter;
	// 逻辑中心
	BusinessLogic * _businessLogic;
	// 背景
	Sprite * _bg;
};


#endif
