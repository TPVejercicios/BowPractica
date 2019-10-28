#include "Arrow.h"

Arrow::Arrow(Texture* t) {
	pos.setX(0);
	pos.setY(50);
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
	if (disparada){// && pos.getX() > 1920) {				//1920 por ejemplo para cuando se sale de la pantalla que deje de moverse;
		pos.setX(pos.getX() + dir.getX() * VELOCITYA);
	}
}


void Arrow::handleEvents(const SDL_Event event) {

}

void Arrow::recargar(int posYArco) {
	pos.setX(0);
	pos.setY(posYArco);		//Obtener de alguna forma la posicion del arco
}