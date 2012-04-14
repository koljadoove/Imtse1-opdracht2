/*
 * OptieScherm.cpp
 *
 *  Created on: 3 mrt. 2012
 *      Author: acer
 */

#include "OptieScherm.h"

bool geraakt;

OptieScherm::OptieScherm( Screen* parent )
{
	//sla schermgrootte op in globale variabelen
	MAExtent screenSize = maGetScrSize();
	int screenWidth = EXTENT_X( screenSize );
	int screenHeight = EXTENT_Y( screenSize );

	//sla parent scherm op (FotoScherm) om de show() te kunnen aanroepen, zodat dit optiescherm weer gesloten wordt
	this->parent = parent;

	//standaard font en grafisch uiterlijk (uit de resource file res.lst)
	Font* font = new MAUI::Font(RES_FONT);
	WidgetSkin* skin = new WidgetSkin( RES_SELECTED, RES_UNSELECTED, 16, 32, 16, 32, false, false );

	//maak een label die andere widgets straks bevat, en een achtergrondkleur heeft
	Label* label = new Label(0,0,0,0,NULL);

	//stel achtergrondkleur in
	label->setBackgroundColor(0x000000);

	// zet standaard widget in als bovenstaande label (wisselt met FotoScherm)
	this->setMain( label );

	//maak listbox met rood, groen en blauw selectie
//	this->rodeLabel = new Label (0,0,100,100,NULL,"test",0,font);
//	this->groeneLabel = new Label (0,0,100,100,NULL,"test2",0,font);
//	this->lijstKleuren = new ListBox (screenWidth/2-50, 155, 80, 30, label);
//	lijstKleuren->add(rodeLabel);
//	lijstKleuren->add(groeneLabel);
//	lijstKleuren->update();

	//maak rode knop
	this->rodeLabel = new Label( screenWidth/2-50, 155, 80, 30, label, " Rood:", 0, font );
	rodeLabel->setSkin( skin );
	this->kleurLabels.add( rodeLabel );	//voeg toe aan vector

	//maak groene knop
	this->groeneLabel = new Label( screenWidth/2-50, 190, 80, 30, label, " Groen:", 0, font );
	groeneLabel->setSkin( skin );
	this->kleurLabels.add( groeneLabel );	//voeg toe aan vector

	//maak blauwe knop
	this->blauweLabel = new Label( screenWidth/2-50, 225, 80, 30, label, " Blauw:", 0, font );
	blauweLabel->setSkin( skin );
	this->kleurLabels.add( blauweLabel );	//voeg toe aan vector

	//maak pastoe knop
	this->pastoeLabel = new Label( screenWidth/2-50, 275, 80, 30, label, " Pas toe", 0, font );
	pastoeLabel->setSkin( skin );

	//stel naam plaatje in m.b.v. editbox
	this->imageTekst = new EditBox( 50, 50, 150, 30, label, "Leuke afbeelding", 0x555500, font, true, false, 20, EditBox::IM_STANDARD );
	this->imageTekst->setSkin(skin);
	imageTekst->setPaddingLeft(5);
	imageTekst->setPaddingTop(5);

	//stel breedte plaatje in m.b.v. editbox
	this->imageSize = new EditBox( 50, 80, 40, 30, label, "150", 0x555500, font, true, false, 3, EditBox::IM_QWERTY);
	this->imageSize->setSkin(skin);
	imageSize->setPaddingLeft(5);
	imageSize->setPaddingTop(5);
}


OptieScherm::~OptieScherm()
{
	//verwijder objecten van deze klasse
}


//Bij drukken op knop, verander selectie
void OptieScherm::keyPressEvent(int keyCode, int nativeCode)
{
	for( int i= 0; i<kleurLabels.size(); i++ )
	{
		if (keyCode == MAK_DOWN)
		{
			if (kleurLabels[0]->isSelected()) // van rood naar groen
			{
				achtergrondKleur = 0x00ff00;
				kleurLabels[0]->setSelected(false);
				kleurLabels[1]->setSelected(true);
				break;
			}
			else if (kleurLabels[1]->isSelected())// van groen naar blauw
			{
				achtergrondKleur= 0x0000ff;
				kleurLabels[1]->setSelected(false);
				kleurLabels[2]->setSelected(true);
				break;
			}
		}
		if (keyCode == MAK_UP)
		{
			if (kleurLabels[2]->isSelected()) // van blauw naar groen
			{
				achtergrondKleur = 0x00ff00;
				kleurLabels[2]->setSelected(false);
				kleurLabels[1]->setSelected(true);
				break;
			}
			else if (kleurLabels[1]->isSelected())// van groen naar rood
			{
				achtergrondKleur = 0xff0000;
				kleurLabels[1]->setSelected(false);
				kleurLabels[0]->setSelected(true);
				break;
			}
		}
	}


	if (keyCode == MAK_FIRE)
	{
		parent->show();
	}
}


// Bij touch...
void OptieScherm::pointerPressEvent(MAPoint2d point)
{
	//... doorloop alle kleurlabels om selectie in te stellen...
	for( int i= 0; i<kleurLabels.size(); i++ )
	{
		// ... controleer of er label is geraakt. Dit is nodig om deselecten bij klik niet op label te voorkomen.
		if (kleurLabels[i]->contains( point.x, point.y))
		{
			geraakt = true;
		}
		else if(!geraakt)
		{
			geraakt = false;
		}
	}

	// als er inderdaad een label geraakt is, controleer welk label dit is, en stel kleur in.
	if (geraakt)
	{
		geraakt = false;
		for( int i= 0; i<kleurLabels.size(); i++ )
		{
			if ( kleurLabels[i]->contains( point.x, point.y) )
			{
				kleurLabels[i]->setSelected(true);
				if (i == 0 ) // rood
				{
					achtergrondKleur = 0xff0000;
				}
				else if (i == 1) // groen
				{
					achtergrondKleur = 0x339900;
				}
				else if (i == 2 ) // blauw
				{
					achtergrondKleur= 0x0000ff;
				}
			}
			else
			{
				kleurLabels[i]->setSelected(false);
			}
		}
	}

	if ( imageTekst->contains(point.x, point.y) )
	{
		imageTekst->setSelected(true);
	}
	else
	{
		imageTekst->setSelected(false);
	}

	if (imageSize->contains(point.x, point.y))
	{
		imageSize->setSelected(true);
	}
	else
	{
		imageSize->setSelected(false);
	}

	if (imageSize->contains(point.x, point.y))
	{
		imageSize->setSelected(true);
	}
	else
	{
		imageSize->setSelected(false);
	}


	if ( pastoeLabel->contains(point.x, point.y ) )
	{
		parent->show();
	}
}

//geef ingestelde achtergrondkleur terug
int OptieScherm::getAchtergrondOptie()
{
	return this->achtergrondKleur;
}

//geef ingestelde ImageSize van de editbox terug
int OptieScherm::getImageSize()
{
	grootte = atoi( this->imageSize->getCaption().c_str() );
	return grootte; //caption is de text in een editbox
}


//geef ingestelde ImageTekst van de editbox terug
const BasicString<char> OptieScherm::getImagetekst()
{
	return this->imageTekst->getCaption(); //caption is de text in een editbox
}

