#include "Skill.h"
#include "Layer/Particle.h"

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
	_type = type;
	switch( type )
	{
		case SkillType::Ligtning:
			log( "skill is ligtning" );

			break;
		case SkillType::Meteor:
			createMeteor( info->getVect( ) );
			break;
		case SkillType::Wind:
			log( "skill is wind" );

			break;
		default:
			break;
	}

	auto physic = EventListenerPhysicsContact::create( );
	physic->onContactBegin = CC_CALLBACK_1( SkillSprite::contact, this );
	_eventDispatcher->addEventListenerWithSceneGraphPriority( physic, this );
	return true;
}
bool SkillSprite::contact( PhysicsContact & con)
	{
		log( "on contact begin ");
		return false;
	}


void SkillSprite::startSkill( )
{
	if( _type == SkillType::Meteor )
	{
		return;
	}
	setCallBack( );
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

void SkillSprite::createMeteor( Vec2 * point )
{
	
	this->setPosition( point->x - 70, _director->getVisibleSize( ).height + 5 );
}
