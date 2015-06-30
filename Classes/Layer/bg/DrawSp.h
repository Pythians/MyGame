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

#ifndef __DrawSp_H_
#define __DrawSp_H_

#include "Config.h"
#include "BusinessLogic/VectArrProcess.h"

USING_NS_CC;



class DrawSp :public DrawNode
{

public:
	bool init( );
	void drawVectArr( VectArr * va );
	void drawVectArrBt( VectArr * va);
	void drawSolidVectArr( VectArr * va );
	void drawSolidVectArrBt( VectArr * va );
	//void drawBezier( const Bezier & bz, const Color4F & color, int seg = 30 );
	
	void drawRoad( const Vec2 * vec, unsigned int seg, 
				   const Vec2 & offset, const Color4F & color );

	CREATE_FUNC( DrawSp );
protected:
	DrawSp( );
	~DrawSp( );

private:

};

#endif