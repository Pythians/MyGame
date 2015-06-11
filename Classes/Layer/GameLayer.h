/*
* GameLayer.h
* Demo
* Used: game layer background
* Create by K on 15/4/16
* Last change by K on 15/4/16
*/


#ifndef GameLayer_H_
#define GameLayer_H_

#include "Config.h"

class GameLayer : public cocos2d::Node
{
public:
	GameLayer( );
	~GameLayer( );

	virtual bool init( );
	bool init( const std::string& filename );
	bool initWithFrame( cocos2d::SpriteFrame* frame );
	bool initWithFrameName( const std::string& frameName );

	virtual void update( float delta );
	virtual void onEnter( );

	float getSpeed( )const;
	void setSpeed( float speed );

	static GameLayer* create( );
	static GameLayer* create( const std::string& filename );
	static GameLayer* createWithFrame( cocos2d::SpriteFrame * frame );
	static GameLayer* createWithFrameName( const std::string& frameName );
private:
	cocos2d::Sprite *_bg1, *_bg2;
	float _speed;
};

#endif