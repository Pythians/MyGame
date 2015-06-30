#include "BgLayer.h"

bool BgLayer::init( )
{
	if( !Node::init( ) )
	{
		return false;
	}
	auto vsize = _director->getVisibleSize( );
	auto lines = _lineLayer->getLines( );
	
	auto arr = new VectArr*[ lines.size( )];
	for( int i = 0; i < lines.size( ); i++ )
	{
		lines[ i ] *= vsize;
		arr[ i ] = new VectArr( lines[ i ] );
	}
	arr[ 0 ]->stichingToBottom( );
	auto d = DrawSp::create( );
	d->drawSolidVectArrBt( arr[ 0 ] );
	this->addChild( d );
	for( int i = 1; i < lines.size( ); i++ )
	{
		auto l = arr[ 0 ]->stiching( arr[ i ] );
		l->stichingToBottom( );
		auto dl = DrawSp::create( );
		dl->drawSolidVectArrBt( l );
		this->addChild( dl );
	}


	return true;
}

BgLayer * BgLayer::create( LineLayer * linelayer )
{
	auto ref = new ( std::nothrow )BgLayer( linelayer );
	if( ref && ref->init( ) )
	{
		ref->autorelease( );
		return ref;
	}
	else
	{
		delete ref;
		return nullptr;
	}
}

BgLayer::BgLayer( LineLayer * linelayer )
	: _lineLayer( linelayer )
{
}

BgLayer::~BgLayer( )
{
	delete _lineLayer;
}
