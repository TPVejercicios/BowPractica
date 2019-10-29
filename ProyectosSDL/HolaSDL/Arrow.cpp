#include "Arrow.h"
#include "Game.h"

Arrow::Arrow(Texture* t, Texture* t2, int r) {
	restantes = r - 1;
	pos.setX(0);
	pos.setY(disT);
	dir.setX(1);
	dir.setY(0);
	texture = t;
	texture2 = t2;
	arrowHead = new SDL_Rect();
	arrowHead->h = y;
	arrowHead->w = x/5;
	arrowHead->x = pos.getX() + 80;
	arrowHead->y = pos.getY();
};


void Arrow::render(SDL_Renderer* renderer) const {
	SDL_Rect* des = new SDL_Rect();
	des->x = pos.getX();
	des->y = pos.getY();
	des->w = x;
	des->h = y;
	SDL_RenderCopy(renderer, texture->getTexture(), nullptr, des); // Copia en buffer
}


void Arrow::renderHUD(SDL_Renderer* renderer) const {
	SDL_Rect* des = new SDL_Rect();
	des->y = hudY;
	des->w = hudW;
	des->h = hudH;
	for (int i = 0; i < restantes; i++) {
		des->x = hudX + i * 10;
		SDL_RenderCopy(renderer, texture2->getTexture(), nullptr, des); // Copia en buffer
	}
}

void Arrow::update() {		//Valores que no me dan confianza, debería poder acceder a las variables globales WEIGHT Y HEIGHT
	arrowHead->x = pos.getX() + 80;
	arrowHead->y = pos.getY();

	if (!disparada) {
		pos.setY(pos.getY() + dir.getY() * VELOCITYC);
		if (pos.getY() < disT) {
			pos.setY(disT);
		}
		else if (pos.getY() > WIN_HEIGHT - y - disD) {
			pos.setY(WIN_HEIGHT - y - disD);
		}
	}
	if (disparada && pos.getX() < WIN_WIDTH) {				
		pos.setX(pos.getX() + dir.getX() * VELOCITYA);
	}
	else if (pos.getX() <= WIN_WIDTH) {
		finDisparo = true;
	}
}


void Arrow::handleEvents(const SDL_Event event, const int posYArco) {
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_DOWN && !disparada) {	//Tecla abajo
			dir.setY(1);
		}
		else if (event.key.keysym.sym == SDLK_UP && !disparada) {	//Tecla ariba
			dir.setY(-1);
		}
		else if (event.key.keysym.sym == SDLK_RIGHT) {	//Tecla disparo
			disparada = true;
			dir.setX(1);
		}
		else if (event.key.keysym.sym == SDLK_LEFT && disparada && finDisparo) {	//Tecla disparo
			recargar(posYArco);
		}
	}
	else {
		dir.setY(0);
	}
}

void Arrow::recargar(const int posYArco) {
	if (restantes > 0) {
		finDisparo = false;
		disparada = false;
		pos.setX(0);
		pos.setY(posYArco + disT);		//Obtener de alguna forma la posicion del arco
		restantes--;
	}
}