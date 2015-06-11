#include "HelloWorldScene.h"

#include "CCPhysicsBody.h"
#include "LayerColorWithPhysicsBody.h"
#include "InteractiveControlCenter.h"
#include "ManageConter.h"

USING_NS_CC;
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    scene->getPhysicsWorld()->setGravity( Vect( 0.0f, -Director::getInstance()->getVisibleSize().height ) );
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

	this->addChild( LayerColor::create( Color4B( 255, 255, 255, 255 ) , DesVesSize.width-100, DesVesSize.height-100) );

	this->addChild( InteractiveControlCenter::create( ) );

	/*auto manage = new ManageConter( );
	manage->addNode( , this );*/

	NotificationCenter::getInstance( )->addObserver( manage, 
													 callfuncO_selector(ManageConter::callBack),
													 M2_LOGIC,
													 nullptr 
													 );

	Vec2 points[ ] =
	{
		Vec2( 0,0 ),
		Vec2( 100,20 ),
		Vec2( 300,50 ),
		Vec2( 400,100 ),
		Vec2( 600,80 ),
		Vec2( 960,50 )
	};

	auto layer = LayerColorWithPhysicsBody::create( );
	layer->setEdgeChain( points, 6 );
	this->addChild( layer );


    return true;
}

void HelloWorld::onEnter()
{
    Layer::onEnter();
    //auto contacListener = EventListenerPhysicsContact::create();
    //
    //contacListener->onContactBegin=[](PhysicsContact& contact)
    //{
    //    log("physics contact event listener begin");
    //    return true;
    //};
    //
    //contacListener->onContactPreSolve=[](PhysicsContact& contact,
    //                                     PhysicsContactPreSolve& solve)
    //{
    //    log("physics contact event listener pre solve");
    //    return true;
    //};
    //
    //contacListener->onContactPostSolve=[](PhysicsContact& contact, const PhysicsContactPostSolve& solve)
    //{
    //    log("physics contact event listener post solve");
    //};
    //
    //contacListener->onContactSeperate=[](PhysicsContact& contact)
    //{
    //    log("physics contact event listener seperate");
    //};
    //
    //Director::getInstance()->getEventDispatcher()->
    //                    addEventListenerWithSceneGraphPriority(contacListener,
    //                                                           this);
}

void HelloWorld::callback( Ref * sender )
{
	auto m = dynamic_cast< InformationCarrier* >( sender );
	log( " %f %f ", m->getVect( ).x, m->getVect( ).y );
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
	//this->removeAllChildren( );
	//Director::getInstance( )->replaceScene( HelloWorld::createScene( ) );
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
#endif
}
