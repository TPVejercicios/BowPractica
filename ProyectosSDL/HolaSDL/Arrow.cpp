#include "Arrow.h"
#include "Game.h"

Arrow::~Arrow() {
	texture->liberar();
	texture2->liberar();
	arrowHead = nullptr;
	game = nullptr;
}

//Crea una flecha
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

//Renderiza una flecha en movimiento
void Arrow::render(SDL_Renderer* renderer) const {
	SDL_Rect* des = new SDL_Rect();
	des->x = pos.getX();
	des->y = pos.getY();
	des->w = x;
	des->h = y;
	SDL_RenderCopy(renderer, texture->getTexture(), nullptr, des); // Copia en buffer
}

//Renderiza las flechas que aparecen en el HUD
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

//Actualiza la posición de la flecha mientras viaja
void Arrow::update() {		
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

//Controla todos los eventos referentes al input ¿OSCAR por qué tienes esto aquí?
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

//Comprueba las flechas que quedan y recarga si es posible
void Arrow::recargar(const int posYArco) {
	if (restantes > 0) {
		finDisparo = false;
		disparada = false;
		pos.setX(0);
		pos.setY(posYArco + disT);		//Obtener de alguna forma la posicion del arco
		restantes--;
	}
}