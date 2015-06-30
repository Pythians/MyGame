#include "DrawSp.h"
#include "BusinessLogic/VectArrProcess.h"

bool DrawSp::init( )
{
	if( !DrawNode::init( ) )
	{
		return false;
	}


	return true;
}

void DrawSp::drawVectArr( VectArr * va )
{
	drawPoly( va->getLines( ), va->getCount( ), false, va->getColor( ) );
}

void DrawSp::drawVectArrBt( VectArr * va )
{
	drawPoly( va->getLines( ), va->getCountToBottom( ), false, va->getColor( ) );
}

void DrawSp::drawSolidVectArr( VectArr * va )
{
	drawSolidPoly( va->getLines( ), va->getCount( ), va->getColor( ) );
}

void DrawSp::drawSolidVectArrBt( VectArr * va )
{
	drawSolidPoly( va->getLines( ), va->getCountToBottom( ), va->getColor( ) );
}


//void DrawSp::drawSolidQuadBezierToBottom( const Vec2 & origin,
//										  const Vec2 & control,
//										  const Vec2 & destination,
//										  unsigned int segments,
//										  const Color4F & color
//										  )
//{
//	int add = 1;
//	Vec2* vertices = new ( std::nothrow ) Vec2[ segments + 3 ];
//	if( !vertices )
//		return;
//
//	getBezier( vertices, segments, origin, destination, control );
//
//	if( destination.y )
//	{
//		vertices[ segments + add ].x = destination.x;
//		vertices[ segments + add ].y = 0;
//		add += 1;
//	}
//	if( origin.y )
//	{
//		vertices[ segments + add ].x = origin.x;
//		vertices[ segments + add ].y = 0;
//		add += 1;
//	}
//	drawPolygon( vertices, segments + add, color, 0.0f, Color4F::BLACK );
//}
//
//void DrawSp::drawSolidCubicBezierToBottom( const Vec2 & origin,
//										   const Vec2 & control1,
//										   const Vec2 & control2,
//										   const Vec2 & destination,
//										   unsigned int segments,
//										   const Color4F & color
//										   )
//{
//	int add = 1;
//	Vec2* vertices = new ( std::nothrow ) Vec2[ segments + 1 ];
//	if( !vertices )
//		return;
//
//	getBezier( vertices, segments, origin, destination, control1, control2 );
//
//	if( destination.y )
//	{
//		vertices[ segments + add ].x = destination.x;
//		vertices[ segments + add ].y = 0;
//		add += 1;
//	}
//	if( origin.y )
//	{
//		vertices[ segments + add ].x = origin.x;
//		vertices[ segments + add ].y = 0;
//		add += 1;
//	}
//	drawPolygon( vertices, segments + add, color, 0.0f, Color4F::RED );
//}
//void DrawSp::drawSolidBezierToBottom( const Bezier & bz, const Color4F & color, int seg )
//{
//	//drawSolidCubicBezierToBottom( bz.begin, bz.control1, bz.control2, bz.end, seg, color );
//}
//
//void DrawSp::drawBezier( const Bezier & bz, const Color4F & color, int seg )
//{
//	if( bz.control2.isZero( ) )
//	{
//		drawQuadBezier( bz.begin, bz.control1, bz.end, seg, color );
//	}
//	else
//	{
//		drawCubicBezier( bz.begin, bz.control1, bz.control2, bz.end, seg, color );
//	}
//}

void DrawSp::drawRoad( const Vec2 * vec, unsigned int seg,
					   const Vec2 & offset, const Color4F & color )
{

}

DrawSp::DrawSp( )
{
}

DrawSp::~DrawSp( )
{
}
