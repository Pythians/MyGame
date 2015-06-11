#include "GameScene.h"
#include "InteractiveControlCenter.h"
#include "LayerColorWithPhysicsBody.h"
#include "Resource/ResourcesManage.h"
#include "Layer/BgLayer.h"

#include "base/firePngData.h"

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

	//this->addChild( LayerColor::create( Color4B( 0, 162, 232, 255 ) ) );

	//auto bz = Bezier( 200.0f, 200.0f, 600.0f, 500.0f, 400.0f, 200.0f, 400.0f, 500.0f );
	//auto va = VectArr( bz );
	//auto li = va.getLines( );

	//auto res = new ResourcesManage( );
	//log( res->getRootPath( ).c_str( ) );
	//auto files = res->getFolders( );
	//for( int i = 0; i < files->size( ); i++ )
	//{
	//	log( files->at( i ).c_str( ) );
	//}
	//auto data = res->getBgLayerDataFromFile( "lines" );
	//auto li = data->getLineLayer( );
	//auto bg = BgLayer::create( li->at( 0 ) );
	//this->addChild( bg );
	//auto bg1 = BgLayer::create( li->at( 1 ) );
	//this->addChild( bg1 );
	//auto bg2 = BgLayer::create( li->at( 2 ) );
	//this->addChild( bg2 );
	//res->release( );
	/*// 创建背景
	//_bg = Sprite::create( "Alps.jpg" );
	//auto bgSize = _bg->getContentSize( );
	//_bg->setPosition( bgSize / 2 );

	//auto body = PhysicsBody::createBox( bgSize );
	//body->setGravityEnable( true );
	//body->setRotationEnable( false );
	//_bg->setPhysicsBody( body );
	//this->addChild( _bg, 0, SP_BG );*/
	//int r = 50;// _director->getVisibleSize( ).height * TRPERCENTILE;
	//auto sp = Sprite::create( );
	//sp->setPosition( 0, 0 );
	//this->addChild( sp );

	//auto bd = PhysicsBody::createEdgeChain( li, va.getCount( ) );
	//bd->setGravityEnable( false );
	//sp->setPhysicsBody( bd );

	//auto layer = LayerColorWithPhysicsBody::create( );
	//layer->setEdgeChain( LINES_0, 7 );
	//_bg->addChild( layer );
	//_manageConter->addNode( LAYER_1, layer );

	//auto layer1 = LayerColorWithPhysicsBody::create( );
	//layer1->setEdgeChain( LINES_1, 7 );
	//_bg->addChild( layer1 );

	//auto ball = Sprite::create( );
	//ball->setPosition( 150, 2*200 + r );
	//this->addChild( ball );
	//auto pb = PhysicsBody::createBox( Size(50,50), PhysicsMaterial( 0.08, 0.5, 1 ), Vec2::ZERO );
	//ball->setPhysicsBody( pb );


	//Texture2D* texture = nullptr;
	//Image* image = nullptr;
	//do
	//{
	//	bool ret = false;
	//	const std::string key = "/__firePngData";
	//	texture = Director::getInstance( )->getTextureCache( )->getTextureForKey( key );
	//	CC_BREAK_IF( texture != nullptr );

	//	image = new ( std::nothrow ) Image( );
	//	CC_BREAK_IF( nullptr == image );
	//	ret = image->initWithImageData( __firePngData, sizeof( __firePngData) );
	//	CC_BREAK_IF( !ret );

	//	texture = Director::getInstance( )->getTextureCache( )->addImage( image, key );
	//} while( 0 );

	//CC_SAFE_RELEASE( image );
	
	//auto pt = ParticleSystemQuad::createWithTotalParticles( 20 );
	//pt->setTexture( texture );
	//pt->setPhysicsBody( pb );
	//pt->setLife( 10.0f );
	//pt->setPosition( 200, 400 );
	//this->addChild( pt );

	//pb->applyForce( Vect( 30000, 0 ) );
	//pb->applyImpulse( Vec2( 20000, -40000) );
	//pb->setCategoryBitmask( 1 );
	//pb->setCollisionBitmask( 1 );
	//pb->setContactTestBitmask( 1 );
	//layer->setBitMask( 1 );
	//layer1->setBitMask( 1 );
	//pb->setGravityEnable( false );

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
