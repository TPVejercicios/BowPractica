#include "Arrow.h"
#include <iostream>
using namespace std;

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