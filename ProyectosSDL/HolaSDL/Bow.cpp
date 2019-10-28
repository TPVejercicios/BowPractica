#include "Bow.h"

Bow::Bow(Texture* t) { 
	texture = t;
	pos.setX(0);
	pos.setY(0);
	dir.setX(0);
	dir.setY(0);
}

void Bow::render(SDL_Renderer* renderer) const {	
	SDL_Rect* des = new SDL_Rect();
	des->x = pos.getX();
	des->y = pos.getY();
	des->w = x;
	des->h = y; 
	SDL_RenderCopy(renderer, texture->getTexture(), nullptr, des); // Copia en buffer
}

void Bow::update() {
	pos.setY(pos.getY() + dir.getY() * VELOCITYB);
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
	}
	else {
		dir.setY(0);
	}

}