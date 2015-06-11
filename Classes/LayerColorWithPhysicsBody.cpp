//
//  LayerColorWithPhysicsBody.cpp
//  Demo
//
//  Created by HK on 15/3/17.
//
//

#include "LayerColorWithPhysicsBody.h"


LayerColorWithPhysicsBody::LayerColorWithPhysicsBody( )
	: LayerColor( )
	, _body( new Vector<PhysicsBody *>( ) )    // 分配内存地址
	, mask( 0 )
{
}
LayerColorWithPhysicsBody::~LayerColorWithPhysicsBody( )
{
	if( !_body->empty( ) )   // 清除数据
	{
		_body->clear( );
	}
	// 释放指针内存
	CC_SAFE_DELETE( _body );
}

LayerColorWithPhysicsBody * LayerColorWithPhysicsBody::create( )
{
	auto ret = new ( std::nothrow )LayerColorWithPhysicsBody( );
	if( ret && ret->init( ) )
	{
		ret->autorelease( );
	}
	else
	{
		CC_SAFE_DELETE( ret );
	}
	return ret;
}

LayerColorWithPhysicsBody * LayerColorWithPhysicsBody::create( const Color4B& color,
															   GLfloat width,
															   GLfloat height )
{
	auto ret = new ( std::nothrow )LayerColorWithPhysicsBody( );
	if( ret && ret->initWithColor( color, width, height ) )
	{
		ret->autorelease( );
	}
	else
	{
		CC_SAFE_DELETE( ret );
	}
	return ret;
}

LayerColorWithPhysicsBody * LayerColorWithPhysicsBody::create( const Color4B& color )
{
	auto ret = new ( std::nothrow )LayerColorWithPhysicsBody( );
	if( ret && ret->initWithColor( color ) )
	{
		ret->autorelease( );
	}
	else
	{
		CC_SAFE_DELETE( ret );
	}
	return ret;
}

void LayerColorWithPhysicsBody::onEnter( )
{
	LayerColor::onEnter( );
	//auto contacListener = EventListenerPhysicsContact::create( );

	//contacListener->onContactBegin = [ ]( PhysicsContact& contact )
	//{
	//	log( "physics contact event listener begin" );
	//	return true;
	//};

	//contacListener->onContactPreSolve = [ ]( PhysicsContact& contact,
	//										 PhysicsContactPreSolve& solve )
	//{
	//	log( "physics contact event listener pre solve" );
	//	return true;
	//};

	//contacListener->onContactPostSolve = [ ]( PhysicsContact& contact, const PhysicsContactPostSolve& solve )
	//{
	//	log( "physics contact event listener post solve" );
	//};

	//contacListener->onContactSeperate = [ ]( PhysicsContact& contact )
	//{
	//	log( "physics contact event listener seperate" );
	//};

	//Director::getInstance( )->getEventDispatcher( )->
	//	addEventListenerWithSceneGraphPriority( contacListener, this );

}

//
//bool LayerColorWithPhysicsBody::init( )
//{
//	return initWithColor( Color4B( 0, 0, 0, 0 ),
//						  WinSize.width,
//						  WinSize.height );
//}
//
//bool LayerColorWithPhysicsBody::initWithColor( const Color4B& color )
//{
//	Size s = Director::getInstance( )->getWinSize( );
//	return initWithColor( color, s.width, s.height );
//}
//bool LayerColorWithPhysicsBody::initWithColor( const Color4B& color,
//											   GLfloat width,
//											   GLfloat height )
//{
//	if( !LayerColor::initWithColor( color, width, height ) )
//	{
//		return false;
//	}
//
//	auto size = this->getContentSize( );
//	log( "LayerColor size w: %f, h: %f", size.width, size.height );
//
//	return true;
//}


void LayerColorWithPhysicsBody::setEdgeSegment( const Vec2 & a,
												const Vec2 & b,
												const PhysicsMaterial & material,
												float border )
{
	auto segment = PhysicsBody::createEdgeSegment( a,
												   b,
												   material,
												   border );
	setBodyMask( segment, mask );
	this->setPhysicsBody( segment );
}

void LayerColorWithPhysicsBody::setEdgePolygon( const Vec2 * points,
												int count,
												const PhysicsMaterial & material,
												float border )
{
	auto polygon = PhysicsBody::createEdgePolygon( points, count, material, border );
	setBodyMask( polygon, mask );
	this->setPhysicsBody( polygon );
}

void LayerColorWithPhysicsBody::setEdgeChain( const Vec2 * points,
											  int count,
											  const PhysicsMaterial & material,
											  float border )
{
	auto chain = PhysicsBody::createEdgeChain( points, count, material, border );
	setBodyMask( chain, mask );
	this->setPhysicsBody( chain );
}

void LayerColorWithPhysicsBody::setEdgeBox( const Size & size,
											const PhysicsMaterial & material,
											float border,
											const Vec2 & offset )
{
	auto box = PhysicsBody::createEdgeBox( size, material, border, offset );
	setBodyMask( box, mask );
	this->setPhysicsBody( box );
}

void LayerColorWithPhysicsBody::createPolygon( const Vec2 * points,
											   int count,
											   Sprite * sprite,
											   const PhysicsMaterial & material,
											   const Vec2 & offset )
{
	auto body = PhysicsBody::createPolygon( points, count, material, offset );
	setBodyMask( body, mask );
	_body->pushBack( body );
	if( sprite != nullptr )
	{
		sprite->setPhysicsBody( body );
	}
}

void LayerColorWithPhysicsBody::createCircle( float radius,
											  Sprite * sprite,
											  const PhysicsMaterial & material,
											  const Vec2 & offset )
{
	auto body = PhysicsBody::createCircle( radius, material, offset );
	setBodyMask( body, mask );
	_body->pushBack( body );
	if( sprite != nullptr )
	{
		sprite->setPhysicsBody( body );
	}
}

void LayerColorWithPhysicsBody::createBox( const Size & size,
										   Sprite * sprite,
										   const PhysicsMaterial & material,
										   const Vec2 & offset )
{
	auto body = PhysicsBody::createBox( size, material, offset );
	setBodyMask( body, mask );
	_body->pushBack( body );
	if( sprite != nullptr )
	{
		sprite->setPhysicsBody( body );
	}
}

void LayerColorWithPhysicsBody::createbody( float mass,
											float moment,
											Sprite * sprite )
{
	auto body = PhysicsBody::create( mass, moment );
	setBodyMask( body, mask );
	_body->pushBack( body );
	if( sprite != nullptr )
	{
		sprite->setPhysicsBody( body );
	}
}

void LayerColorWithPhysicsBody::setBodyMask( PhysicsBody * body, int ditmask )
{
	body->setCategoryBitmask( mask );
	body->setCollisionBitmask( mask );
	body->setContactTestBitmask( mask );
}

void LayerColorWithPhysicsBody::setBitMask( int ditmask )
{
	mask = ditmask;
	auto body = this->getPhysicsBody( );
	if( body != nullptr )
	{
		body->setCategoryBitmask( mask );
		body->setCollisionBitmask( mask );
		body->setContactTestBitmask( mask );
	}
	for( int i = 0; i < _body->size( ); i++ )
	{
		_body->at( i )->setCategoryBitmask( mask );
		_body->at( i )->setCollisionBitmask( mask );
		_body->at( i )->setContactTestBitmask( mask );
	}
}

int LayerColorWithPhysicsBody::getBitMask( )
{
	return mask;
}
