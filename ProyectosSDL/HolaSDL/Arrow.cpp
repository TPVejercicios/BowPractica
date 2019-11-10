#include "Arrow.h"
#include "Game.h"

Arrow::~Arrow() {
	try {
		texture = nullptr;
		delete arrowHead;
		delete arrowFull;
		cout << "Flecha eliminada" << endl;
	}
	catch (exception e) {
		cout << "Error deleting an arrow" << e.what() << endl;
	}
}

//Crea una flecha
Arrow::Arrow(Texture* t) {
	texture = t;
	pos.setX(0);
	pos.setY(disT);
	dir.setX(1);
	dir.setY(0);
	//El rect de la flecha entera para renderizarla
	arrowFull = new SDL_Rect();
	arrowFull->x = pos.getX();
	arrowFull->y = pos.getY();
	arrowFull->w = texture->getW() / SCALE_DIV;
	arrowFull->h = texture->getH() / SCALE_DIV;
	//El rect de la punta de la flecha, evitando el palo para detectar las colisiones
	arrowHead = new SDL_Rect();
	arrowHead->h = 5;  //texture->getH() / 4;
	arrowHead->w = texture->getW() / 100;
	arrowHead->x = pos.getX() + gap;
	arrowHead->y = pos.getY();
};

//Renderiza una flecha en movimiento
void Arrow::render() {
	if (shooted) texture->render(*arrowFull, SDL_FLIP_NONE);
}

//Actualiza la posición de la flecha mientras viaja
void Arrow::update() {
	if (shooted) {
		pos.setX(pos.getX() + (dir.getX() * ARROW_SPEED));
		arrowFull->x = pos.getX();
		arrowFull->y = pos.getY();
		arrowHead->x = pos.getX() + gap;
		arrowHead->y = pos.getY();
	}
}

void Arrow::shootArrow(Vector2D shootPos) {
	pos = shootPos;
	shooted = true;
}