
#include "ManageConter.h"
#include "Config.h"

ManageConter::ManageConter( )
	: _node( new Map<int, Node*> )
	, _skill( nullptr )
	, _people( new Vector<Sprite*> )
{
	//NotificationCenter::getInstance( )->addObserver( this,
	//												 callfuncO_selector( ManageConter::callBack ),
	//												 M2_LOGIC,
	//												 nullptr
	//												 );
}

ManageConter::~ManageConter( )
{
	_node->clear( );
	_people->clear( );
	CC_SAFE_DELETE( _node );
	CC_SAFE_DELETE( _people );
	NotificationCenter::getInstance( )->removeAllObservers( this );
}

ManageConter * ManageConter::create( )
{
	auto ref = new ( std::nothrow ) ManageConter( );
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

void ManageConter::callBack( Ref * sender )
{
	auto m = dynamic_cast< InformationCarrier* >( sender );
	int size = m->getVectSize( );
	auto vect = m->getVect( );
	for( int i = 0; i < size; i++ )
	{
		log( "- %f - %f -", vect[ i ].x, vect[ i ].y );
	}
}

void ManageConter::addNode( const LayerKey key, Node * node ) const
{
	node->retain( );
	_node->insert( key, node );
}

void ManageConter::setSkill( SkillSprite * skill )
{
	_skill = skill;
	_node->at( LAYER_BASE )->addChild( skill );
	//skill->startSkill( );
}


