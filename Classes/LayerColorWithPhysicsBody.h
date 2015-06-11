//
//  LayerColorWithPhysicsBody.h
//  Demo
//
//  Created by HK on 15/3/17.
//
//

#ifndef __Demo__LayerColorWithPhysicsBody__
#define __Demo__LayerColorWithPhysicsBody__

#include "cocos2d.h"
#include "physics/CCPhysicsBody.h"
#include "Config.h"

USING_NS_CC;

class LayerColorWithPhysicsBody : public LayerColor
{
public:


    // 创建默认颜色,默认大小 LayerColor
	static LayerColorWithPhysicsBody * create( );
    // 创建指定颜色,大小的LayerColor
	static LayerColorWithPhysicsBody * create( const Color4B& color,
											   GLfloat width,
											   GLfloat height );
    // 创建指定颜色,默认大小的LayerColor
	static LayerColorWithPhysicsBody * create( const Color4B& color );

	void onEnter( );

protected:
	LayerColorWithPhysicsBody( );
	virtual ~LayerColorWithPhysicsBody( );
    // 初始化
	//bool init( );
	//bool initWithColor( const Color4B& color,
	//					GLfloat width,
	//					GLfloat height );
	//bool initWithColor( const Color4B& color );


private:
	// mask 碰撞参数
	int mask;
	// Save physics bodys
	CC_SYNTHESIZE_READONLY( Vector<PhysicsBody *> *, _body, Body );
public:

    /*
    * 创建物理边界
    * 线条 多边形 链条 方框
    * 前一个或两个参数 指定边界的大小位置
    * 后两个参数设定物理特性(有默认值)
    * Box 的最后一个参数指定位置
    */
	// Create and set PhysicsBody edge
	void setEdgeSegment( const Vec2& a,
						 const Vec2& b,
						 const PhysicsMaterial& material = PHYSICSBODY_MATERIAL_DEFAULT,
						 float border = 1 );
	void setEdgePolygon( const Vec2* points,
						 int count,
						 const PhysicsMaterial& material = PHYSICSBODY_MATERIAL_DEFAULT,
						 float border = 1 );
	void setEdgeChain( const Vec2* points,
					   int count,
					   const PhysicsMaterial& material = PHYSICSBODY_MATERIAL_DEFAULT,
					   float border = 1 );
	void setEdgeBox( const Size& size,
					 const PhysicsMaterial& material = PHYSICSBODY_MATERIAL_DEFAULT,
					 float border = 1,
					 const Vec2& offset = Vec2::ZERO );
    
    /*
    * 创建物理 Body
    * 多边形 圆 方框 body
    * 前一个或两个参数 创建 Body 特征
    * Sprite 绑定的精灵
    * 后两个参数设定物理特性(有默认值)
    * Box 的最后一个参数指定位置
    */
	// Create PhysicsBody
	void createPolygon( const Vec2* points,
						int count,
						Sprite * sprite = nullptr,
						const PhysicsMaterial& material = PHYSICSBODY_MATERIAL_DEFAULT,
						const Vec2& offset = Vec2::ZERO );
	void createCircle( float radius,
					   Sprite * sprite = nullptr,
					   const PhysicsMaterial& material = PHYSICSBODY_MATERIAL_DEFAULT,
					   const Vec2& offset = Vec2::ZERO );
	void createBox( const Size& size,
					Sprite * sprite = nullptr,
					const PhysicsMaterial& material = PHYSICSBODY_MATERIAL_DEFAULT,
					const Vec2& offset = Vec2::ZERO );
	void createbody( float mass = 0.0, float moment = 0.0, Sprite * sprite = nullptr );

	// 设置碰撞组， 同一 Layer ditmask 相同
	void setBodyMask( PhysicsBody * body, int ditmask );
	//  设置更新 mask
	void setBitMask( int mask );
	int getBitMask( );

};


#endif /* defined(__Demo__LayerColorWithPhysicsBody__) */
