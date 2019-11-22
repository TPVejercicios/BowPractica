#include "Butterfly.h"

void Butterfly::update() {
	pos.setY(pos.getY() + dir.getY() * MAX_SPEED);
	pos.setX(pos.getX() + dir.getX() * MAX_SPEED);

	if (pos.getX() > MAX_X || pos.getX() < MIN_X ) {
		dir.setX(-dir.getX());
		dir.setY(dir.getY());
		flip = SDL_FLIP_HORIZONTAL;
	}
	else if (pos.getY() > MAX_Y || pos.getY() < 0) {
		dir.setX(dir.getX());
		dir.setY(-dir.getY());
		flip = SDL_FLIP_HORIZONTAL;
	}
}

//Falta la animación
void Butterfly::render()const {
	texture->renderFrame(getRect(),0,0,flip);
}