#include "GameScene.h"
#include "InteractiveControlCenter.h"
#include "Layer/GameLayer.h"

bool GameScene::init( )
{
	if( !Layer::init( ) )
	{
		return false;
	}
	// 管理中心初始化
	_manageConter = ManageConter::create( );
	// 添加 BASE 层
	_manageConter->addNode( LAYER_BASE, this );
	// 逻辑中心初始化
	_businessLogic = BusinessLogic::create( _manageConter );
	_businessLogic->retain( );
	// 触摸控制层初始化
	auto touch = InteractiveControlCenter::create( );
	// 添加到 BASE
	this->addChild( touch, 100 );
	// 添加到管理中心
	_manageConter->addNode( LAYER_Touch, touch );

	//this->addChild( GameLayer::create( ) );



	return true;
}


Scene * GameScene::createScene( )
{
	// 创建物理世界 默认重力 (-98)
	auto scene = Scene::createWithPhysics( );
	scene->getPhysicsWorld( )->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_ALL );

	auto layer = GameScene::create( );

	scene->addChild( layer );

	return scene;
}
