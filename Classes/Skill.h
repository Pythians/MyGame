
/*
* SpriteIt.h
* Demo
* Used: create custome sprite
* 
* Create by K on 15/4/4
* Last change by K on 15/4/7
*/

#ifndef _SpriteIt_H_
#define _SpriteIt_H_

#include "cocos2d.h"
#include "Config.h"

USING_NS_CC;

class SkillSprite : public Sprite
{
public:
	SkillSprite( );
	~SkillSprite( );

	static SkillSprite * create( SkillType type, InformationCarrier * info );
	// 重写父类 create 
	static SkillSprite * create( );
	static SkillSprite * create( const std::string& fileName );
private:
	bool initWithSkillType( SkillType & type, InformationCarrier * info );
	// 自定义动作
	Action * _action;
	// 回调
	std::function<void( )> _callBack;

public:
	// 外部调用接口
	// 开始动作
	void startSkill( );
	// 设置动作 若参数为 nullpter 使用默认动作
	void setAction( Action * action = nullptr );
	// 设置回调 若参数为 nullpter 使用默认回调
	void setCallBack( std::function<void( )> call = nullptr );
};

#endif