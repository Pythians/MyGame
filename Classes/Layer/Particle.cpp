#include "Particle.h"

MyParicle::MyParicle( )
{
}


MyParicle::~MyParicle( )
{
}

void MyParicle::setDefaultTexture( )
{
	auto texture = _director->getTextureCache( )->addImage( "Particle.png" );
	if( texture != nullptr )
	{
		setTexture( texture );
	}
}


bool MyParicle::initFire( )
{
	if( initWithTotalParticles( 75 ) )
	{
		setDefaultTexture( );
		// duration
		_duration = DURATION_INFINITY;

		// Gravity Mode
		this->_emitterMode = Mode::GRAVITY;

		// Gravity Mode: gravity
		this->modeA.gravity = Vec2( 0, 0 );
		//this->modeA.rotationIsDir = true;
		// Gravity Mode: radial acceleration
		this->modeA.radialAccel = 0;
		this->modeA.radialAccelVar = 0;

		// Gravity Mode: speed of particles
		this->modeA.speed = 70;
		this->modeA.speedVar = 10;

		// starting angle
		_angle = 90;
		_angleVar = 10;

		// emitter position
		Size winSize = Director::getInstance( )->getWinSize( );
		this->setPosition( winSize.width / 2, 60 );
		_posVar = Vec2( 10, 3 );
		// life of particles
		_life = 0.55;
		_lifeVar = 0.05f;

		// size, in pixels
		_startSize = 5.0f;
		_startSizeVar = 0.5f;
		_endSize = START_SIZE_EQUAL_TO_END_SIZE;

		// emits per frame
		_emissionRate = _totalParticles / _life;

		// color of particles
		_startColor.r = 0.76f;
		_startColor.g = 0.25f;
		_startColor.b = 0.12f;
		_startColor.a = 1.0f;
		_startColorVar.r = 0.0f;
		_startColorVar.g = 0.0f;
		_startColorVar.b = 0.0f;
		_startColorVar.a = 0.0f;
		_endColor.r = 0.0f;
		_endColor.g = 0.0f;
		_endColor.b = 0.0f;
		_endColor.a = 1.0f;
		_endColorVar.r = 0.0f;
		_endColorVar.g = 0.0f;
		_endColorVar.b = 0.0f;
		_endColorVar.a = 0.0f;

		// additive
		this->setBlendAdditive( true );
		return true;
	}
	return false;
}

bool MyParicle::initMeteor( )
{
	if( initWithTotalParticles( 100 ) )
	{
		setDefaultTexture( );

		// duration
		_duration = DURATION_INFINITY;

		// Gravity Mode
		this->_emitterMode = Mode::RADIUS;

		modeB.startRadius = 10.0f;
		modeB.startRadiusVar = 0.0f;
		modeB.endRadius = 30.0f;
		modeB.endRadiusVar = 0.0f;
		modeB.rotatePerSecond = 0.0f;
		modeB.rotatePerSecondVar = 0.0f;

		// starting angle
		_angle = 270.0f;
		_angleVar = 10.0f;

		// emitter position
		Size winSize = Director::getInstance( )->getWinSize( );
		this->setPosition( winSize.width / 2, 60 );
		_posVar = Vec2( 10, 3 );
		// life of particles
		_life = 0.5f;
		_lifeVar = 0.1f;

		// size, in pixels
		_startSize = 5.0f;
		_startSizeVar = 0.5f;
		_endSize = 1.0f;

		// emits per frame
		_emissionRate = _totalParticles / _life;

		// color of particles
		_startColor.r = 0.76f;
		_startColor.g = 0.25f;
		_startColor.b = 0.12f;
		_startColor.a = 1.0f;
		_startColorVar.r = 0.0f;
		_startColorVar.g = 0.0f;
		_startColorVar.b = 0.0f;
		_startColorVar.a = 0.0f;
		_endColor.r = 1.0f;
		_endColor.g = 1.0f;
		_endColor.b = 1.0f;
		_endColor.a = 1.0f;
		_endColorVar.r = 0.0f;
		_endColorVar.g = 0.0f;
		_endColorVar.b = 0.0f;
		_endColorVar.a = 0.0f;

		// additive
		this->setBlendAdditive( true );
		return true;
	}
	return false;
}

MyParicle * MyParicle::createFire( )
{
	auto ret = new ( std::nothrow )MyParicle( );
	if( ret && ret->initFire( ) )
	{
		ret->autorelease( );
	}
	else
	{
		CC_SAFE_DELETE( ret );
	}
	return ret;
}

MyParicle * MyParicle::createMeteor( )
{
	auto ret = new ( std::nothrow )MyParicle( );
	if( ret && ret->initMeteor( ) )
	{
		ret->autorelease( );
	}
	else
	{
		CC_SAFE_DELETE( ret );
	}
	return ret;
}
