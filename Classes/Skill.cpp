#include "Skill.h"

SkillSprite::SkillSprite( )
	: _action( nullptr )
	, _callBack( nullptr )
{
}

SkillSprite::~SkillSprite( )
{
}

SkillSprite * SkillSprite::create( SkillType type, InformationCarrier * info )
{
	auto ret = new ( std::nothrow )SkillSprite( );
	if( ret && ret->initWithSkillType( type, info ) )
	{
		ret->autorelease( );
		return ret;
	}
	CC_SAFE_DELETE( ret );
	return nullptr;
}

SkillSprite * SkillSprite::create( )
{
	auto ret = new ( std::nothrow )SkillSprite( );
	if( ret && ret->init( ) )
	{
		ret->autorelease( );
		return ret;
	}
	CC_SAFE_DELETE( ret );
	return nullptr;
}

SkillSprite * SkillSprite::create( const std::string & fileName )
{
	auto ret = new ( std::nothrow )SkillSprite( );
	if( ret && ret->initWithFile( fileName ) )
	{
		ret->autorelease( );
		return ret;
	}
	CC_SAFE_DELETE( ret );
	return nullptr;
}

bool SkillSprite::initWithSkillType( SkillType & type, InformationCarrier * info )
{
	if( !Sprite::init( ) )
	{
		return false;
	}

	switch( type )
	{
		case SkillType::Ligtning:
			log( "skill is ligtning" );

			break;
		case SkillType::Meteor:
			log( "skill is Meteor" );

			break;
		case SkillType::Wind:
			log( "skill is wind" );

			break;
		default:
			break;
	}

	return true;
}

void SkillSprite::setAction( Action * action )
{
	if( action )
	{
		_action = action;
	}
	else
	{
		auto move = MoveBy::create( 1.0f, Vec2( 100, 0 ) );
		_action = Sequence::create( move, CallFunc::create( _callBack ), nullptr );
	}
}

void SkillSprite::startSkill( )
{
	setCallBack( );
	setAction( );
	this->runAction( _action );
}

void SkillSprite::setCallBack( std::function<void( )> call )
{
	if( call == nullptr )
	{
		_callBack = [ this ]( ) { log( "Sprite call back" ); this->removeFromParent( ); };
	}
	else
	{
		_callBack = call;
	}
}
