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
#ifndef _VectArrProcess_H_
#define _VectArrProcess_H_

#include "Config.h"
#include "Data/Data.h"
using cocos2d::Vect;
using cocos2d::Vec4;
using std::swap;

bool Equal( float x, float y );
class VectArr
{

public:
	VectArr( const Bezier & bz, int conut = 30 )
		: _bezier( bz )
		, _count( conut )
		, _bottom( 0 )
	{
		_lines = new Vect[ _count + 2 ];
		getBezier( bz );
	}
	VectArr( int count = 30 )
		: _count( count )
		, _bottom( 0 )
	{
		_lines = new Vect[ count + 2];
	}
	~VectArr( )
	{
		delete[ ]_lines;
	}
private:
	Bezier _bezier;
	Vect * _lines;
	int _count;
	int _bottom;
public:
	Bezier getBezier( ) const;
	Color4F getColor( ) const;
	void setColor(const Color4F & c );
	Vect * getLines( ) const;
	void setCountToBottom( int count );
	int getCountToBottom( );
	void setCount( int count );
	int getCount( ) const;
	VectArr * stiching( VectArr * other );
public:
	int Intersection( Vect v1, Vect v2, Vect v3, Vect v4, Vect & out );
	cocos2d::Vec4 V2V4( const Vect & l, const Vect & r );
	// return Rect( xMin, yMin, xMax, yMax )
	cocos2d::Vec4 getMaxVec4( );
	cocos2d::Vec4 getBigRect( const cocos2d::Vec4 & r1, const cocos2d::Vec4 & r2 );
	bool isMixVec( const cocos2d::Vec2 & l1, const cocos2d::Vec2 & l2,
				   const cocos2d::Vec2 & r1, const cocos2d::Vec2 & r2 );
	void offsetVects( const Vect & offset );
	void offsetVects( unsigned int begin, unsigned int end, const Vect& offset );
	void stichingToBottom( );
protected:
	bool isSimple( );
	bool isSimpleX( );
	bool isSimpleY( );

	Vect * getBezier( const Bezier & bz );
	Vect * getBezier( const Vect & from,
					  const Vect & to,
					  const Vect & control1,
					  const Vect & control2 = Vect::ZERO
					  );
	void copy( Vect * in, int & begin, int & end , Vect * out, int & ins);
	int getLastIndex( Vect * v, int & count, const Vect & p );
};

#endif