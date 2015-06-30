#include "GameLayer.h"
#include "Resource/ResourcesManage.h"
#include "Layer/bg/BgLayer.h"

USING_NS_CC;

GameLayer::GameLayer( )
{
}

GameLayer::~GameLayer( )
{
}

bool GameLayer::init( )
{
	if( !Node::init( ) )
	{
		return false;
	}
	this->addChild( LayerColor::create( Color4B( 182, 228, 254, 255 ) ) );

	auto size = _director->getVisibleSize( );
	auto cloud = createCloud( );
	cloud->setScale( 0.6 );
	cloud->setPosition( size.width * 0.81, size.height * 0.90 );
	this->addChild( cloud );

	auto cloud1 = createCloud( );
	cloud1->setScale( 0.5 );
	cloud1->setPosition( size.width * 0.5, size.height * 0.92 );
	this->addChild( cloud1 );

	auto cloud2 = createCloud( );
	cloud2->setScale( 0.4 );
	cloud2->setPosition( size.width * 0.162, size.height * 0.84 );
	this->addChild( cloud2 );

	auto res = new ResourcesManage( );
	auto data = res->getBgLayerDataFromFile( "lines" );
	auto li = data->getLineLayer( );
	for( auto l : *li )
	{
		this->addChild( BgLayer::create( l ) );
	}
	/*for( int i = 0; i < li->size( ); i++ )
	{
		auto bg = BgLayer::create( li->at( i ) );
		this->addChild( bg );
	}*/
	res->release( );

	return true;
}

Node * GameLayer::createCloud( )
{
	Color4F color = Color4F( 0.929f, 0.972f, 1.0f, 1.0f );
	auto circle = DrawNode::create( );
	circle->drawSolidCircle( Vec2::ZERO, 60.0f, 0.0f, 24, color );
	circle->setPosition( 0, 0 );
	auto circle1 = DrawNode::create( );
	circle1->drawSolidCircle( Vec2::ZERO, 35.0f, 0.0f, 24, color );
	circle1->setPosition( 50, -15 );
	auto circle2 = DrawNode::create( );
	circle2->drawSolidCircle( Vec2::ZERO, 40.0f, 0.0f, 24, color );
	circle2->setPosition( -50, -10 );
	auto circle3 = DrawNode::create( );
	circle3->drawSolidCircle( Vec2::ZERO, 25.0f, 0.0f, 24, color );
	circle3->setPosition( -80, -22 );

	auto cloud = Node::create( );
	cloud->addChild( circle3 );
	cloud->addChild( circle2 );
	cloud->addChild( circle1 );
	cloud->addChild( circle );
	return cloud;
}
