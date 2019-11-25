#include "Butterfly.h"
#include "Game.h"

void Butterfly::update() {

	if (currState == ALIVE) {
		pos.setY(pos.getY() + dir.getY() * MAX_SPEED);
		pos.setX(pos.getX() + dir.getX() * MAX_SPEED);

		if (currCol >= 5) {
			currCol = 0;
		}
		else
		{
			currCol++;
		}
	}
	else
	{
		pos.setY(pos.getY() + DEAD_DIR * DEAD_SPEED);
		if (pos.getY() > MAX_Y && !deleting) {
			deleting = true;
			game->killObject(this);
		}

	}

	//Comprobar colisiones con los límites de la pantalla
	if (pos.getX() > MAX_X || pos.getX() < MIN_X ) {
		dir.setX(-dir.getX());
		dir.setY(dir.getY());
		flip = SDL_FLIP_VERTICAL;
	}
	else if (pos.getY() > MAX_Y || pos.getY() < 0) {
		dir.setX(dir.getX());
		dir.setY(-dir.getY());
		flip = SDL_FLIP_HORIZONTAL;

	}
}

//Falta la animación
void Butterfly::render()const {
	texture->renderFrame(getRect(),currRow,currCol,flip);
}

void Butterfly::startDestruction() {
	collisionable = false;
	currState = DEAD;
}