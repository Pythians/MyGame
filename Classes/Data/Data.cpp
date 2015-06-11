#include "Data.h"


Bezier operator*( const Bezier& l, const Vect& r )
{
	return Bezier( l.begin.x * r.x, l.begin.y* r.y,
				   l.end.x * r.x, l.end.y * r.y,
				   l.control1.x * r.x, l.control1.y * r.y,
				   l.control2.x * r.x, l.control2.y * r.y,
				   l.color );
}
Bezier & operator *=( Bezier & l, const Vect & r )
{
	l.begin.x *= r.x; l.begin.y *= r.y;
	l.end.x *= r.x; l.end.y *= r.y;
	l.control1.x *= r.x; l.control1.y *= r.y;
	l.control2.x *= r.x; l.control2.y *= r.y;
	return l;
}

void Bezier::offset( const Vect & offset )
{
	begin += offset;
	end += offset;
	control1 += offset;
	control2 += offset;
}



LineLayer::LineLayer( )
{
}

LineLayer::~LineLayer( )
{
	_lines.clear( );
}


void LineLayer::AddBezier( float b1, float b2, float e1, float e2,
						   float c11, float c12, float c21, float c22 )
{
	_lines.push_back( Bezier( b1, b2, e1, e2, c11, c12, c21, c22 ) );
}

void LineLayer::AddBezier( float b1, float b2, float e1, float e2,
						   float c11, float c12, float c21, float c22,
						   float r, float g, float b, float a )
{
	_lines.push_back( Bezier( b1, b2, e1, e2, c11, c12, c21, c22, r, g, b, a ) );
}

std::vector<Bezier> LineLayer::getLines( ) const
{
	return _lines;
}

bool LineLayer::isEmpty( ) const
{
	return _lines.empty( );
}

BgLayerData::BgLayerData( )
	: _lineLayer( new std::vector< LineLayer*> )
{
}

BgLayerData::~BgLayerData( )
{
	_lineLayer->clear( );
	delete _lineLayer;
}

void BgLayerData::AddLineLayer( LineLayer * l )
{
	_lineLayer->push_back( l );
}

std::vector<LineLayer *> * BgLayerData::getLineLayer( ) const
{
	return _lineLayer;
}
