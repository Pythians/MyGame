﻿//
//  Config.h
//  Demo
//
//  Created by HK on 15/6/1.
//  Last change by K on 15/6/1
//

#ifndef __Data_H_
#define __Data_H_

#include "cocos2d.h"

using cocos2d::Vect;
using cocos2d::Color4F;

typedef struct Bezier
{
	Vect begin;
	Vect end;
	Vect control1;
	Vect control2;
	Color4F color;

	Bezier( ) { }
	Bezier( Vect b, Vect e, Vect c1, Vect c2, Color4F c )
		: begin( b )
		, end( e )
		, control1( c1 )
		, control2( c2 )
		, color( c )
	{
	}

	Bezier( float b1, float b2, float e1, float e2,
			float c11, float c12, float c21, float c22,
			float r = 0, float g = 0, float b = 0, float a = 0 )
		: begin( Vect( b1, b2 ) )
		, end( Vect( e1, e2 ) )
		, control1( Vect( c11, c12 ) )
		, control2( Vect( c21, c22 ) )
		, color( Color4F( r, g, b, a ) )
	{
	}
	Bezier( float b1, float b2, float e1, float e2,
			float c11, float c12, float c21, float c22,
			Color4F c )
		: begin( Vect( b1, b2 ) )
		, end( Vect( e1, e2 ) )
		, control1( Vect( c11, c12 ) )
		, control2( Vect( c21, c22 ) )
		, color( c )
	{
	}
	~Bezier( ) { }
	void offset( const Vect & offset );
}Bezier;

Bezier& operator *=( Bezier & l, const Vect & r );
Bezier operator*( const Bezier& l, const Vect& r );

class LineLayer
{
public:
	LineLayer( );
	~LineLayer( );

	void AddBezier( float b1, float b2, float e1, float e2,
					float c11, float c12, float c21, float c22 );
	void AddBezier( float b1, float b2, float e1, float e2,
					float c11, float c12, float c21, float c22,
					float r, float g, float b, float a );
	std::vector<Bezier> getLines( ) const;
	bool isEmpty( )const;
private:
	std::vector<Bezier> _lines;
};

class BgLayerData
{
public:
	BgLayerData( );
	~BgLayerData( );

	void AddLineLayer( LineLayer * l );
	std::vector<LineLayer*> * getLineLayer( ) const;
private:
	std::vector<LineLayer*> * _lineLayer;
};


#endif