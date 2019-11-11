#include "Ballon.h"
#include <iostream>
using namespace std;

//Destructora de Ballon
Ballon::~Ballon() {

	try {
		texture = nullptr;
		game = nullptr;
		delete ballonBody;
		cout << "Se ha eliminado un globo " << endl;
	}
	catch (exception e) {
		cout << "Error deleting ballon" << e.what() << endl;
	}
}

//Renderiza el globo
void Ballon::render() const {
	texture->renderFrame(*ballonBody, numTexture,collFrame,1,SDL_FLIP_NONE);
}

//Mueve el globo en función de su velocidad
//Segund implementación meter el objecto a una lista de objectos a borrar
void Ballon::update() {
	if (status == SWOLLEN) {
		ballonBody->x = pos.getX() + gap;
		ballonBody->y = pos.getY() + gap;
		pos.subVectorInY(vel);
		//game->checkCrushBallon();
		if (pos.getY() < -100) {//Si el ballon sale por arriba con un extra de 100 para que se vea como sale de escena
			//Aqui llamar a killObject();
		}
	}
	else
	{
		collFrame++;
		if (collFrame > texture->getNumCols()) {
			//killObject();
		}
	}
}
