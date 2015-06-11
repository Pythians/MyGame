/*
* BusinessLogic.h
* Demo
* Used: 

* Create by K on 15/4/7
* Last change by K on 15/4/7
*/

#ifndef _BusinessLogic_H_
#define _BusinessLogic_H_

#include "ManageConter.h"

class ManageConter;

class BusinessLogic : public Ref
{
public:
	static BusinessLogic * create( ManageConter * manage );
protected:
	BusinessLogic( ManageConter * manage );
	~BusinessLogic( );

private:
	void receiveMsg( Ref * sender );

	void skillMeteor( InformationCarrier * info );
	void skillWind( InformationCarrier * info );
	void skillLigtning( InformationCarrier * info );
	ManageConter * _manage;
};

#endif