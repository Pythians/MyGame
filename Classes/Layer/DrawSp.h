/*
* ResourcesManage.h
* Demo
* Used: Manage Resourse
*
* Create by K on 15/5/14
* Last change by K on 15/6/4
*/

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