

/*
* ManageConter.h
* Demo
* Use: Manage sprite, layer, resouce
*
* Create by K on 15/4/4
* Last change by K on 15/4/4
*/


#ifndef _ManageConter_H_
#define _ManageConter_H_

#include "Config.h"
#include "Skill.h"
#include "BusinessLogic.h"

class ManageConter : public Ref
{
	friend class BusinessLogic;
protected:
	ManageConter( );
	~ManageConter( );
private:

	Map<int, Node*> * _node;
	Sprite * _skill;
	Vector<Sprite*> * _people;
public:
	static ManageConter * create( );
	void callBack( Ref*sender );

	void addNode( const LayerKey key, Node * node ) const;
	void setSkill( SkillSprite * skill );
};



#endif