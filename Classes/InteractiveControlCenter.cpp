

#include "InteractiveControlCenter.h"

InteractiveControlCenter::InteractiveControlCenter( )
	: _drawNode( nullptr )
{
}

InteractiveControlCenter::~InteractiveControlCenter( )
{
}

bool InteractiveControlCenter::init( )
{
	if( !Layer::init( ) )
	{
		return false;
	}
	setColor( );
	// 添加触摸事件
	auto touchListener = EventListenerTouchOneByOne::create( );
	touchListener->setSwallowTouches( false );
	touchListener->onTouchBegan = CC_CALLBACK_2( InteractiveControlCenter::onTouchBegan,
												 this );
	touchListener->onTouchMoved = std::bind( &InteractiveControlCenter::onTouchMoved,
											 this,
											 std::placeholders::_1,
											 std::placeholders::_2 );
	touchListener->onTouchEnded = std::bind( &InteractiveControlCenter::onTouchEnded,
											 this,
											 std::placeholders::_1,
											 std::placeholders::_2 );
	touchListener->onTouchCancelled = std::bind( &InteractiveControlCenter::onTouchCancelled,
												 this,
												 std::placeholders::_1,
												 std::placeholders::_2 );

	_eventDispatcher->addEventListenerWithSceneGraphPriority( touchListener, this );
	// 添加键盘监听
	auto keyboard = EventListenerKeyboard::create( );
	keyboard->onKeyPressed = [ ]( EventKeyboard::KeyCode key, Event * event )
	{
		switch( key )
		{
			case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_BREAK:
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE:
				Director::getInstance( )->end( );
				break;
			default:
				break;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority( keyboard, this );
	return true;
}

bool InteractiveControlCenter::onTouchBegan( cocos2d::Touch * touch, Event * unused_event )
{
	// 清空记录触摸点
	for( int i = 0; i < VECTSIZE; i++ )
	{
		_vec[ i ] = Vec2::ZERO;
	}
	// 保存起始点
	_vec[ 0 ] = touch->getLocation( );
	// 初始化绘图节点
	if( _drawNode )
	{
		_drawNode->setVisible( true );
	}
	else
	{
		_drawNode = DrawNode::create( );
		// 设置位置
		this->addChild( _drawNode );
		// 绘制触摸点 (角度 15 24 条边 )
		_drawNode->drawSolidCircle( Vec2::ZERO,
									_director->getVisibleSize( ).height * TRPERCENTILE,
									15,
									24,
									_color
									);
	}
	_drawNode->setPosition( _vec[ 0 ] );
	return true;
}

void InteractiveControlCenter::onTouchMoved( cocos2d::Touch * touch, Event * unused_event )
{
	// 更新触摸点
	_drawNode->setPosition( touch->getLocation( ) );
	// 触摸点数组中添加当前点
	for( int i = 1; i < VECTSIZE; i++ )
	{
		if( _vec[ VECTSIZE - i ] == Vec2::ZERO && _vec[ VECTSIZE - i - 1 ] != Vec2::ZERO )
		{
			_vec[ VECTSIZE - i ] = touch->getLocation( );
			break;
		}
	}
}

void InteractiveControlCenter::onTouchEnded( cocos2d::Touch * touch, Event * unused_event )
{
	// 移除点
	_drawNode->runAction( Sequence::create( DelayTime::create( 0.1f ),
											CCCallFuncN::create( [ ]( Node * node )->void { node->setVisible( false ); } ),
											nullptr ) );
	int size = 0;
	for( int i = 0; i < VECTSIZE; i++ )
	{
		if( _vec[ i ] == Vec2::ZERO )
		{
			size = i;
			break;
		}
	}
	NotificationCenter::getInstance( )->postNotification( M2_LOGIC,
														  InformationCarrier::create( SkillType::None,
																					  _vec,
																					  size,
																					  0,
																					  nullptr )
														  );
}

void InteractiveControlCenter::onTouchCancelled( cocos2d::Touch * touch, Event * unused_event )
{
	log( "touch cancell" );
}

void InteractiveControlCenter::setColor( Color4F color )
{
	_color = color;
}




