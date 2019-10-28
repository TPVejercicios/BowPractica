#include "Arrow.h"

Arrow::Arrow(Texture* t) {
	pos.setX(0);
	pos.setY(44);
	dir.setX(1);
	dir.setY(0);
	texture = t;
};


void Arrow::render(SDL_Renderer* renderer) const {
	SDL_Rect* des = new SDL_Rect();
	des->x = pos.getX();
	des->y = pos.getY();
	des->w = x;
	des->h = y;
	SDL_RenderCopy(renderer, texture->getTexture(), nullptr, des); // Copia en buffer
}

void Arrow::update() {
	if (disparada && pos.getX() > 1000) {				//1920 por ejemplo para cuando se sale de la pantalla que deje de moverse
		pos.setX(pos.getX() + dir.getX() * VELOCITYA);
		pos.setY(pos.getY() + dir.getY() * VELOCITYA);
	}
}


void Arrow::handleEvents(const SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_DOWN) {	//Tecla abajo
			dir.setY(1);
		}
		else if (event.key.keysym.sym == SDLK_UP) {	//Tecla ariba
			dir.setY(-1);
		}
		else if (event.key.keysym.sym == SDLK_RIGHT) {	//Tecla disparo
			dir.setX(1);
		}
		else if (event.key.keysym.sym == SDLK_LEFT) {	//Tecla disparo
			dir.setX(0);
			pos.setX(0);
		}
	}
	else {
		dir.setY(0);
	}
}

void Arrow::recargar(int posYArco) {
	pos.setX(0);
	pos.setY(posYArco);		//Obtener de alguna forma la posicion del arco
}