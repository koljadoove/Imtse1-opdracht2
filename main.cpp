#include <MAUtil/Moblet.h>
#include "FotoBewerker.h"

//main functie
extern "C" int MAMain()
{
	//start een Moblet app met de FotoBewerker klasse
	Moblet::run(new FotoBewerker());
	return 0;
}
