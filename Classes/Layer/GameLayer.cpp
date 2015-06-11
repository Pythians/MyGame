#include "GameLayer.h"

USING_NS_CC;

GameLayer::GameLayer( )
	: _bg1( nullptr )
	, _bg2( nullptr )
	, _speed( 1.0f )
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

	_bg1 = Sprite::create( );
	_bg2 = Sprite::create( );

	return true;
}

bool GameLayer::init( const std::string & filename )
{
	if( !Node::init( ) )
	{
		return false;
	}

	_bg1 = Sprite::create( filename );
	_bg2 = Sprite::create( filename );
	
	return true;
}

bool GameLayer::initWithFrame( cocos2d::SpriteFrame * frame )
{
	if( !Node::init( ) )
	{
		return false;
	}

	_bg1 = Sprite::createWithSpriteFrame( frame );
	_bg2 = Sprite::createWithSpriteFrame( frame );

	return true;
}

bool GameLayer::initWithFrameName( const std::string & frameName )
{
	if( !Node::init( ) )
	{
		return false;
	}

	_bg1 = Sprite::createWithSpriteFrameName( frameName );
	_bg2 = Sprite::createWithSpriteFrameName( frameName );

	return true;
}

void GameLayer::update( float delta )
{
	auto x1 = _bg1->getPositionX( );
	auto x2 = _bg2->getPositionX( );
	auto w = _bg1->getContentSize( ).width;
	if( -x1 > w )
	{
		_bg1->setPosition( x2 + w - 2 - _speed, 0 );
	}
	else
	{
		_bg1->setPositionX( x1 - _speed );
	}
	if( -x2 > w )
	{
		_bg2->setPosition( x1 + w - 2 - _speed, 0 );
	}
	else
	{
		_bg2->setPositionX( x2 - _speed );
	}
}

void GameLayer::onEnter( )
{
	Node::onEnter( );
	_bg1->setAnchorPoint( Vec2::ANCHOR_BOTTOM_LEFT );
	_bg2->setAnchorPoint( Vec2::ANCHOR_BOTTOM_LEFT );
	_bg1->setPosition( Vec2::ZERO );
	_bg2->setPosition( _bg1->getContentSize( ).width - 2, 0 );
    
	this->addChild( _bg1 );
	this->addChild( _bg2 );
	this->scheduleUpdate( );
}


float GameLayer::getSpeed( ) const
{
	return _speed;
}

void GameLayer::setSpeed( float speed )
{
	_speed = speed;
}

GameLayer * GameLayer::create( )
{
	auto ret = new ( std::nothrow ) GameLayer( );
	if( ret && ret->init( ) )
	{
		ret->autorelease( );
		return ret;
	}
	delete ret;
	return nullptr;
}

GameLayer * GameLayer::create( const std::string & filename )
{
	auto ret = new ( std::nothrow ) GameLayer( );
	if( ret && ret->init( filename ) )
	{
		ret->autorelease( );
		return ret;
	}
	delete ret;
	return nullptr;
}

GameLayer * GameLayer::createWithFrame( cocos2d::SpriteFrame * frame )
{
	auto ret = new ( std::nothrow ) GameLayer( );
	if( ret && ret->initWithFrame( frame ) )
	{
		ret->autorelease( );
		return ret;
	}
	delete ret;
	return nullptr;
}

GameLayer * GameLayer::createWithFrameName( const std::string & frameName )
{
	auto ret = new ( std::nothrow ) GameLayer( );
	if( ret && ret->initWithFrameName( frameName ) )
	{
		ret->autorelease( );
		return ret;
	}
	delete ret;
	return nullptr;
}

