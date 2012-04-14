/*
 * FotoBewerker.cpp
 *
 *  Created on: 3 mrt. 2012
 *      Author: acer
 */

#include "FotoBewerker.h"


//constructor maakt een nieuw fotoscherm
FotoBewerker::FotoBewerker()
{
	this->fotoScherm = new FotoScherm();
	fotoScherm->show();
}

//destructor verwijdert fotoscherm
FotoBewerker::~FotoBewerker()
{
	delete this->fotoScherm;
}





/**
 * Called when a key is pressed.
 */
void FotoBewerker::keyPressEvent(int keyCode, int nativeCode)
{
	if (MAK_BACK == keyCode )
	{
		// Call close to exit the application.
		this->close();
	}
}


