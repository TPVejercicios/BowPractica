#include "Bow.h"

Bow::Bow(Texture* t1, Texture* t2) { 
	textureC = t1;
	textureD = t2;
	pos.setX(0);
	pos.setY(0);
	dir.setX(0);
	dir.setY(0);
}

void Bow::render(SDL_Renderer* renderer) const {	
	SDL_Rect* des = new SDL_Rect();
	des->h = y;
	des->y = pos.getY();
	des->y = pos.getY();
	if (cargado) {
		des->x = pos.getX();
		des->w = xC;
		SDL_RenderCopy(renderer, textureC->getTexture(), nullptr, des); // Copia en buffer
	}
	else {
		des->x = pos.getX() + dist;
		des->w = xD;
		SDL_RenderCopy(renderer, textureD->getTexture(), nullptr, des); // Copia en buffer
	}

}

void Bow::update() {
	pos.setY(pos.getY() + dir.getY() * VELOCITYB);
	if (pos.getY() < 0) {
		pos.setY(0);
	}
	else if (pos.getY() > 600 - y) {
		pos.setY(600 - y);
	}
}


void Bow::handleEvents(const SDL_Event event) {
	//No se si esto va en handleEvents o que
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_DOWN) {	//Tecla abajo
			dir.setY(1);
		}
		else if (event.key.keysym.sym == SDLK_UP) {	//Tecla ariba
			dir.setY(-1);
		}
		else if (event.key.keysym.sym == SDLK_RIGHT) {	//Tecla disparo
			cargado = false;
		}
		else if (event.key.keysym.sym == SDLK_LEFT) {	//Tecla disparo
			cargado = true;
		}
	}
	else {
		dir.setY(0);
	}

}