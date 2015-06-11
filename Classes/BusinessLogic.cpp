#include "BusinessLogic.h"

BusinessLogic * BusinessLogic::create( ManageConter * manage )
{
	auto ref = new ( std::nothrow ) BusinessLogic( manage );
	if( ref )
	{
		ref->autorelease( );
	}
	else
	{
		ref = nullptr;
	}
	return ref;
}

BusinessLogic::BusinessLogic( ManageConter * manage )
	: _manage( manage )
{
	_manage->retain( );
	NotificationCenter::getInstance( )->addObserver( this, 
													 callfuncO_selector( BusinessLogic::receiveMsg ),
													 M2_LOGIC,
													 nullptr
													 );
}

BusinessLogic::~BusinessLogic( )
{
	NotificationCenter::getInstance( )->removeAllObservers( this );
}

void BusinessLogic::receiveMsg( Ref * sender )
{
	auto msg = dynamic_cast< InformationCarrier* >( sender );
	auto vec = msg->getVect( );
	auto cou = msg->getVectSize( );
	auto size = Director::getInstance( )->getVisibleSize( );

	for( int i = 0; i < cou; i++ )
	{
		log( "Logic vect  %f %f ", vec[ i ].x, vec[ i ].y );
	}

	if( cou == 1 )
	{
		skillMeteor( msg );
	}
	else if( vec->y < size.height * SKILLDIFFERENTIATE )
	{
		skillWind( msg );
	}
	else
	{
		if( vec[cou - 1].y > size.height * SKILLDIFFERENTIATE )
		{
			log( "No Skill" );
		}
		else
		{
			skillLigtning( msg );
		}
	}
}

void BusinessLogic::skillMeteor( InformationCarrier * info )
{
	_manage->setSkill( SkillSprite::create( Meteor, info ) );
}

void BusinessLogic::skillWind( InformationCarrier * info )
{
	auto line = info->getVect( );
	int t = info->getVectSize( ) / 3;
	for( int i = 1; i < t; i++ )
	{
		line[ i ] = line[ i * 3 - 1 ];
	}
	info->setVectSize( t + 1 );
	_manage->setSkill( SkillSprite::create( SkillType::Wind, info ) );
}

void BusinessLogic::skillLigtning( InformationCarrier * info )
{
	auto line = info->getVect( );
	auto size = info->getVectSize( );
	line->set( line[ size - 1 ] );
	int t = size / 3;
	for( int i = 1; i < t; i++ )
	{
		line[ i ] = line[ i * 3 - 1 ];
	}
	info->setVectSize( t + 1 );
	_manage->setSkill( SkillSprite::create( SkillType::Ligtning, info ) );
}
