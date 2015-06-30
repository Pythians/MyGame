/******************************************************************************
Copyright( c ) 2015 H·K

http://www.cnblogs.com/pythian

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files( the "Software" ), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************************/

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
	SkillType _type;

public:
	// 外部调用接口
	// 开始动作
	void startSkill( );
	// 设置回调 若参数为 nullpter 使用默认回调
	void setCallBack( std::function<void( )> call = nullptr );
protected:
	void createMeteor( Vec2 * point );
	bool contact( PhysicsContact&con );
};

#endif