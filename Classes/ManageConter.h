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


#ifndef _ManageConter_H_
#define _ManageConter_H_

#include "Config.h"
#include "Layer/Skill/Skill.h"
#include "BusinessLogic/BusinessLogic.h"

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