#include "VectArrProcess.h"


bool Equal( float x, float y )
{
	return abs( x - y ) < 1e-4f;
}
// As ==	! To avoid conflicts
bool operator>=( const Vect & v1, const Vect & v2 )
{
	return Equal( v1.x, v2.x ) && Equal( v1.y, v2.y );
}
// As >		! To avoid conflicts
bool operator>>( const Vect & v1, const Vect & v2 )
{
	return v1.x > v2.x || Equal( v1.x, v2.x ) && v1.y > v2.y;
}
// ! Count Outer product 
// v1.x*v2.y - v1.y*v2.x
float operator^( const Vect & v1, const Vect & v2 )
{
	return v1.x*v2.y - v1.y*v2.x;
}

Bezier VectArr::getBezier( ) const
{
	return _bezier;
}

Color4F VectArr::getColor( ) const
{
	return _bezier.color;
}

void VectArr::setColor( const Color4F & c )
{
	_bezier.color = c;
}

Vect * VectArr::getLines( ) const
{
	return _lines;
}

void VectArr::setCountToBottom( int count )
{
	_bottom = count;
}

int VectArr::getCountToBottom( )
{
	return _count + _bottom;
}

void VectArr::setCount( int count )
{
	_count = count;
}


int VectArr::getCount( ) const
{
	return _count;
}

VectArr * VectArr::stiching( VectArr * other )
{
	int dcount = _count;
	int ucount = other->getCount( );
	int sum = dcount + ucount;
	auto varr = new VectArr( sum );
	auto lines = varr->getLines( );
	auto dLine = _lines;
	auto uLine = other->getLines( );
	auto mix = std::vector<Vect>( );
	varr->setColor( other->getColor( ) );

	for( int i = 1; i < dcount; i++ )
	{
		for( int j = 1; j < ucount; j++ )
		{
			if( isMixVec( uLine[ i - 1 ], uLine[ i ],
						  dLine[ j - 1 ], dLine[ j ] ) )
			{
				Vect t;
				int v = Intersection( uLine[ i - 1 ], uLine[ i ],
									  dLine[ j - 1 ], dLine[ j ], t );
				if( v > 0 )
				{
					mix.push_back( t );
				}
			}
		}
	}
	if( mix.empty( ) )
	{
		delete varr;
		return nullptr;
	}
	if( dLine->y > uLine->y )
	{
		swap( uLine, dLine );
		swap( dcount, ucount );
		varr->setColor( _bezier.color );
	}
	int dbe = 0, den = dcount ;
	int ube = 0, ued = ucount;
	int ind = 0;
	switch( mix.size( ) )
	{
		case 1:
		{
			den = getLastIndex( dLine, dcount, mix[ 0 ] );
			ube = getLastIndex( uLine, ucount, mix[ 0 ] );
			copy( dLine, dbe, den, lines, ind );
			lines[ ind ] = mix[ 0 ];
			copy( uLine, ube, ued, lines, ++ind );
			varr->setCount( ind );
			break;
		}
		case 2:
		{
			den = getLastIndex( dLine, dcount, mix[ 0 ] );
			copy( dLine, dbe, den, lines, ind );
			lines[ ind ] = mix[ 0 ];
			ube = getLastIndex( uLine, ucount, mix[ 0 ] );
			ued = getLastIndex( uLine, ucount, mix[ 1 ] );
			copy( uLine, ube, ued, lines, ++ind );
			lines[ ind ] = mix[ 1 ];
			dbe = getLastIndex( dLine, dcount, mix[ 1 ] );
			copy( dLine, dbe, dcount, lines, ++ind );
			varr->setCount( ind );
			break;
		}
		default:
			break;
	}
	return varr;
}

int VectArr::Intersection( Vect p1, Vect p2, Vect p3, Vect p4, Vect & Out )
{
	if( p1 >= p2 || p3 >= p4 )
	{
		return 0;
	}
	if( p1 >> p2 )
	{
		swap( p1, p2 );
	}
	if( p3 >> p4 )
	{
		swap( p3, p4 );
	}
	if( p1 >= p3 && p2 >= p4 )
	{
		return 6;
	}
	auto v1 = Vect( p2.x - p1.x, p2.y - p1.y );
	auto v2 = Vect( p4.x - p3.x, p4.y - p3.y );
	float corss = v1 ^ v2;
	if( p1 >= p3 )
	{
		Out = p1;
		return Equal( corss, 0 ) ? 5 : 3;
	}
	if( p2 >= p4 )
	{
		Out = p2;
		return Equal( corss, 0 ) ? 5 : 3;
	}
	if( p1 >= p4 )
	{
		Out = p1;
		return 3;
	}
	if( p2 >= p3 )
	{
		Out = p2;
		return 3;
	}
	if( p1 >= p3 )
	{
		swap( p1, p3 );
		swap( p2, p4 );
		swap( v1, v2 );
		corss = v1 ^ v2;
	}
	if( Equal( corss, 0 ) )
	{
		auto vs = Vect( p3.x - p1.x, p3.y - p1.y );
		if( Equal( v1^vs, 0 ) )
		{
			if( p2 > p3 )
			{
				Out = p3;
				return 4;
			}
		}
		return 0;
	}

	float ymax1 = p1.y, ymin1 = p2.y, ymax2 = p3.y, ymin2 = p4.y;
	ymax1 < ymin1 ? swap( ymax1, ymin1 ) : 0;
	ymax2 < ymin2 ? swap( ymax2, ymin2 ) : 0;
	if( p1.x > p4.x || p2.x < p3.x || ymax1 < ymin2 || ymin1 > ymax2 )
	{
		return 0;
	}
	auto vs1 = Vect( p1.x - p3.x, p1.y - p3.y );
	auto vs2 = Vect( p2.x - p3.x, p2.y - p3.y );
	auto vt1 = Vect( p3.x - p1.x, p3.y - p1.y );
	auto vt2 = Vect( p4.x - p1.x, p4.y - p1.y );
	float s1v2, s2v2, t1v1, t2v1;
	if( Equal( s1v2 = vs1 ^ v2, 0 ) && p4 >= p1 && p1 >= p3 )
	{
		Out = p1;
		return 2;
	}
	if( Equal( s2v2 = vs2 ^ v2, 0 ) && p4 >= p2 && p2 >= p3 )
	{
		Out = p2;
		return 2;
	}
	if( Equal( t1v1 = vt1 ^ v1, 0 ) && p2 >= p3 && p3 >= p1 )
	{
		Out = p3;
		return 2;
	}
	if( Equal( t2v1 = vt2 ^ v1, 0 ) && p2 >= p4 && p4 >= p1 )
	{
		Out = p4;
		return 2;
	}
	if( s1v2 * s2v2 > 0 || t1v1 * t2v1 > 0 )
	{
		return 0;
	}

	float conA = p1.x * v1.y - p1.y*v1.x;
	float conB = p3.x * v2.y - p3.y*v2.x;

	Out.x = ( conB * v1.x - conA * v2.x ) / corss;
	Out.y = ( conB * v1.y - conA * v2.y ) / corss;
	return 1;
}

cocos2d::Vec4 VectArr::getMaxVec4( )
{
	float xMax = _lines->x, xMin = _lines->x, yMax = _lines->y, yMin = _lines->y;
	for( int i = 0; i < _count; i++ )
	{
		if( xMin > _lines[ i ].x )
		{
			xMin = _lines[ i ].x;
		}
		if( xMax < _lines[ i ].x )
		{
			xMax = _lines[ i ].x;
		}
		if( yMax < _lines[ i ].y )
		{
			yMax = _lines[ i ].y;
		}
		if( yMin > _lines[ i ].y )
		{
			yMin = _lines[ i ].y;
		}
	}
	return cocos2d::Vec4( xMin, yMin, xMax, yMax );
}

cocos2d::Vec4 VectArr::getBigRect( const cocos2d::Vec4 & r1, const cocos2d::Vec4 & r2 )
{
	cocos2d::Vec4 r;
	r1.x > r2.x ? r.x = r1.x : r.x = r2.x;
	r1.y > r2.y ? r.y = r1.y : r.y = r2.y;
	r1.z > r2.z ? r.z = r1.z : r.z = r2.z;
	r1.w > r2.w ? r.w = r1.w : r.w = r2.w;
	return r;
}

bool VectArr::isMixVec( const cocos2d::Vec2 & l1, const cocos2d::Vec2 & l2,
						const cocos2d::Vec2 & r1, const cocos2d::Vec2 & r2 )
{
	float xmax1 = l1.x, xmin1 = l2.x, xmax2 = r1.x, xmin2 = r2.x;
	xmax1 < xmin1 ? swap( xmax1, xmin1 ) : 0;
	xmax2 < xmin2 ? swap( xmax2, xmin2 ) : 0;
	float ymax1 = l1.y, ymin1 = l2.y, ymax2 = r1.y, ymin2 = r2.y;
	ymax1 < ymin1 ? swap( ymax1, ymin1 ) : 0;
	ymax2 < ymin2 ? swap( ymax2, ymin2 ) : 0;
	if( xmax1 < xmin2 || xmin1 > xmax2 || ymax1 < ymin2 || ymin1 > ymax2 )
	{
		return false;
	}
	return true;
}
cocos2d::Vec4 VectArr::V2V4( const Vect & l, const Vect & r )
{
	return cocos2d::Vec4( l.x, l.y, r.x, r.y );
}


bool VectArr::isSimple( )
{
	return isSimpleX( ) && isSimpleY( );
}
bool VectArr::isSimpleX( )
{
	bool b = true;
	float max = _lines->x;
	if( max < _lines[ _count - 1 ].x )
	{
		for( int i = 1; i < _count; i++ )
		{
			if( max > _lines[ i ].x )
			{
				b = false;
				break;
			}
		}
	}
	else
	{
		for( int i = 1; i < _count; i++ )
		{
			if( max < _lines[ i ].x )
			{
				b = false;
				break;
			}
		}
	}
	return b;
}
bool VectArr::isSimpleY( )
{
	bool b = true;
	float max = _lines->y;
	if( max < _lines[ _count - 1 ].y )
	{
		for( int i = 1; i < _count; i++ )
		{
			if( max > _lines[ i ].y )
			{
				b = false;
				break;
			}
		}
	}
	else
	{
		for( int i = 1; i < _count; i++ )
		{
			if( max < _lines[ i ].y )
			{
				b = false;
				break;
			}
		}
	}
	return b;
}

Vect * VectArr::getBezier( const Vect & from,
						   const Vect & to,
						   const Vect & control1,
						   const Vect & control2
						   )
{
	float t = 0.0f;
	if( control2.isZero( ) )
	{
		for( unsigned int i = 0; i < _count; i++ )
		{
			_lines[ i ].x = powf( 1 - t, 2 ) * from.x + 2.0f * ( 1 - t ) * t * control1.x + t * t * to.x;
			_lines[ i ].y = powf( 1 - t, 2 ) * from.y + 2.0f * ( 1 - t ) * t * control1.y + t * t * to.y;
			t += 1.0f / _count;
		}
		_lines[ _count ].x = to.x;
		_lines[ _count ].y = to.y;
	}
	else
	{
		for( unsigned int i = 0; i < _count; i++ )
		{
			_lines[ i ].x = powf( 1 - t, 3 ) * from.x + 3.0f * powf( 1 - t, 2 ) * t * control1.x + 3.0f * ( 1 - t ) * t * t * control2.x + t * t * t * to.x;
			_lines[ i ].y = powf( 1 - t, 3 ) * from.y + 3.0f * powf( 1 - t, 2 ) * t * control1.y + 3.0f * ( 1 - t ) * t * t * control2.y + t * t * t * to.y;
			t += 1.0f / _count;
		}
		_lines[ _count ].x = to.x;
		_lines[ _count ].y = to.y;
	}
	_count += 1;
	return _lines;
}

void VectArr::stichingToBottom( )
{
	if( _lines[ _count - 1 ].y )
	{
		_bottom += 1;
		_lines[ _count -1  + _bottom ].x = _lines[ _count - 1 ].x;
		_lines[ _count - 1 + _bottom ].y = 0;
	}
	if( _lines[ 0 ].y )
	{
		_bottom += 1;
		_lines[ _count - 1 + _bottom ].x = _lines[ 0 ].x;
		_lines[ _count - 1 + _bottom ].y = 0;
	}
}

void VectArr::copy( Vect * in, int & begin, int & end, Vect * out, int & ins )
{
	while( begin < end )
	{
		out[ ins ] = in[ begin ];
		++ins, ++begin;
	}
}

int VectArr::getLastIndex( Vect * v, int & count, const Vect & p )
{
	int i = 0;
	do
	{
		if( v[ i ].x >= p.x ) break; 
		++i;
	} while( i < count );
	return i;
}

Vect * VectArr::getBezier( const Bezier & bz )
{
	return getBezier( bz.begin, bz.end, bz.control1, bz.control2 );
}

void VectArr::offsetVects( const Vect & offset )
{
	for( int i = 0; i < _count + _bottom; i++ )
	{
		_lines[ i ] += offset;
	}
}

void VectArr::offsetVects( unsigned int begin, unsigned int end, const Vect & offset )
{
	begin > end ? swap( begin, end ) : 0;
	for( unsigned int i = begin; i < end; i++ )
	{
		_lines[ i ] += offset;
	}
}