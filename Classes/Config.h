//
//  Config.h
//  Demo
//
//  Created by HK on 15/3/17.
//  Last change by K on 15/4/13
//

#ifndef Demo_Config_h
#define Demo_Config_h

#include "cocos2d.h"
using cocos2d::Vec2;
using std::string;

// post massage sign
const string M2_LOGIC = "2logic";
const string M2_SPRITE = "2sprite";
const string M2_MANAGE = "2manage";


// sprite name
const string SP_BG = "Background";

// Resources Root file
const string r_File = "CloseNormal.png";
const string r_Folder = "Resources";

// vect array size
const int VECTSIZE = 60;
// 触摸点半径和屏幕高的比率
const float TRPERCENTILE = 0.025f;
// 区分技能
const float SKILLDIFFERENTIATE = 0.6f;
//cocos2d::Size VISIBLESIZE = cocos2d::Size( 0, 0 );
const cocos2d::Size DESVESSIZE = cocos2d::Size( 960, 640 );

const Vec2 LINES_0[ ] = {
	Vec2( DESVESSIZE.width * 0,  DESVESSIZE.height * 0 ),
	Vec2( DESVESSIZE.width * 0.1,DESVESSIZE.height * 0.05 ),
	Vec2( DESVESSIZE.width * 0.2,DESVESSIZE.height * 0.09 ),
	Vec2( DESVESSIZE.width * 0.3,DESVESSIZE.height * 0.105 ),
	Vec2( DESVESSIZE.width * 0.4,DESVESSIZE.height * 0.125 ),
	Vec2( DESVESSIZE.width * 0.5,DESVESSIZE.height * 0.15 ),
	Vec2( DESVESSIZE.width * 0.6,DESVESSIZE.height * 0.25 )
};
const Vec2 LINES_1[ ] = {
	Vec2( DESVESSIZE.width * 0.4,DESVESSIZE.height * 0 ),
	Vec2( DESVESSIZE.width * 0.5,DESVESSIZE.height * 0.05 ),
	Vec2( DESVESSIZE.width * 0.6,DESVESSIZE.height * 0.125 ),
	Vec2( DESVESSIZE.width * 0.7,DESVESSIZE.height * 0.15 ),
	Vec2( DESVESSIZE.width * 0.8,DESVESSIZE.height * 0.15 ),
	Vec2( DESVESSIZE.width * 0.9,DESVESSIZE.height * 0.25 ),
	Vec2( DESVESSIZE.width * 1,  DESVESSIZE.height * 0.5 )
}; 

enum LayerKey
{
	LAYER_BASE = 0x0010,
	LAYER_Touch,
	LAYER_1,
	LAYER_2,
	LAYER_3,
	LAYER_4,
	LAYER_5
};

enum SkillType
{
	Wind = 0x0001,
	Meteor,
	Ligtning,
	None
};

class InformationCarrier : public cocos2d::Ref
{
public:
	InformationCarrier( SkillType skill, Vec2 * vect, int vectSize, int hp, void * data )
		: _skill( skill )
		, _vect( vect )
		, _vectSize( vectSize )
		, _hp( hp )
		, _data( data )
	{
	}
	~InformationCarrier( )
	{
	}

	SkillType getSkill( )
	{
		return _skill;
	}
	Vec2 * getVect( )
	{
		return _vect;
	}
	int getVectSize( )
	{
		return _vectSize;
	}
	void setVectSize( int size )
	{
		_vectSize = size;
	}
	int getHP( )
	{
		return _hp;
	}
	void * getData( )
	{
		return _data;
	}

	static InformationCarrier * create( SkillType skill,
										Vec2 * vect,
										int vectSize,
										int hp,
										void * data = nullptr )
	{
		InformationCarrier * ref = new ( std::nothrow )InformationCarrier( skill,
																		   vect,
																		   vectSize,
																		   hp,
																		   data );
		if( ref )
		{
			ref->autorelease( );
		}
		return ref;
	}
private:
	SkillType _skill;
	Vec2 * _vect;
	int _vectSize;
	int _hp;
	void * _data;
};

#endif
