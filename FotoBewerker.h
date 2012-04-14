/*
 * FotoBewerker.h
 *
 *  Created on: 3 mrt. 2012
 *      Author: acer
 */

#ifndef FOTOBEWERKER_H_
#define FOTOBEWERKER_H_


//we gebruiken Screen klasse om schermen aan te maken
#include <MAUtil/Moblet.h>
#include <MAUI/Screen.h>

//deze namespaces zijn nodig om niet overal MAUtil:: en MAUI:: achter bijbehorende klassen te schrijven
using namespace MAUtil;
using namespace MAUI;


//we maken een fotoscherm, dit fotoscherm bevat weer een optiescherm
#include "FotoScherm.h"


//de klasse is een Moblet die events af kan vangen, en opgestart wordt in de main
class FotoBewerker : public Moblet
{
private:
	//fotoscherm
	Screen* fotoScherm;

public:
	FotoBewerker();
	virtual ~FotoBewerker();

	void keyPressEvent( int keyCode, int nativeCode );
};

#endif /* FOTOBEWERKER_H_ */
