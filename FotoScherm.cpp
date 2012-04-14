/*
 * FotoScherm.cpp
 *
 *  Created on: 3 mrt. 2012
 *      Author: acer
 */

#include "FotoScherm.h"

FotoScherm::FotoScherm()
{
	//sla schermgrootte op in globale variabelen
	MAExtent screenSize = maGetScrSize();
	int screenWidth = EXTENT_X( screenSize );
	int screenHeight = EXTENT_Y( screenSize );

	//standaard font en grafisch uiterlijk (uit de resource file res.lst)
	Font* font = new MAUI::Font(RES_FONT);
	WidgetSkin* skin = new WidgetSkin( RES_SELECTED, RES_UNSELECTED, 16, 32, 16, 32, false, false );

	//maak een label die andere widgets straks bevat, en een achtergrondkleur heeft
	achtergrondLabel = new Label(0,0,0,0,NULL);

	//stel achtergrondkleur in
	achtergrondLabel->setBackgroundColor(0x000000);

	// stel width en height in van plaatje
	imageTekst = new Label( screenWidth/2 - 40, 250, 80, 30, achtergrondLabel, "", 0, font);
	imageTekst->setSkin(skin);
	imageTekst->setPaddingLeft(5);
	imageTekst->setPaddingTop(5);
	image = new Image(screenWidth/2-60,screenHeight/2-60, 120, 160, achtergrondLabel, false, false, RES_IMAGE);

	//dit scherm als standaard, met achtergrondlabel als basis widget (wisselt met OptieScherm)
	this->setMain(achtergrondLabel);

	//het optiescherm
	this->optieScherm = new OptieScherm( this );
}


FotoScherm::~FotoScherm()
{

}


//show() override de show() van de super klasse (Screen), omdat we bij showen eerst opties willen ophalen
void FotoScherm::show()
{
	//roep de show() van de superklasse (Screen) aan
	this->Screen::show();

	//haal informatie achtergrondkleur op van optiescherm
	this->achtergrondLabel->setBackgroundColor( this->optieScherm->getAchtergrondOptie() );

	//haal informatie imagetekst op van optiescherm
	imageTekst->setCaption(this->optieScherm->getImagetekst());

	//haal informatie over afmetingen afbeeldingen
	this->image->setWidth(this->optieScherm->getImageSize());
	this->image->setHeight(this->optieScherm->getImageSize());
}


//bij indrukken van de MAK_FIRE toets, laat optiescherm zien
void FotoScherm::keyPressEvent(int keyCode, int nativeCode)
{
	if (keyCode == MAK_FIRE)
	{
		optieScherm->show();
	}
}

//bij touch op scherm, laat optiescherm zien.
void FotoScherm::pointerPressEvent(MAPoint2d point)
{
	optieScherm->show();
}
