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