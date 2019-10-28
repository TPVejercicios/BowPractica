#include "Bow.h"

Bow::Bow(Texture* t) { 
	texture = t;
	pos.setX(0);
	pos.setY(0);
	dir.setX(0);
	dir.setY(0);
	arrow = new Arrow();
	//arrow = new Arrow(textures.at(4));
}

void Bow::render() const {													//Amaro espero que sepas como podemos arreglar esto, pero RenderCopy pide SDL_Texture y Texture 
	//SDL_RenderClear(renderer); // Borra la pantalla
	//SDL_RenderCopy(renderer, texture->getTexture(), nullptr, nullptr); // Copia en buffer
	//SDL_RenderPresent(renderer); // Muestra la escena
}

void Bow::update(SDL_Event event) {
	//No se si esto va en handleEvents o que
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_DOWN) {	//Tecla abajo
			dir.setY(1);
		}
		else if (event.key.keysym.sym == SDLK_UP) {	//Tecla ariba
			dir.setY(-1);
		}
		else if (event.key.keysym.sym == SDLK_LEFT && arrow->getDisparada() == true) {	//Tecla recarga,    Aqui el timing entre recargas?
			arrow->setDisparada(false);
			arrow->recargar((pos.getY() + y) / 2);		//Devuelve la flecha a la posición en medio del arco
		}
	}
	else {
		dir.setY(0);
	}

	//La intuicion me dice que aqui solo debería estar esto
	pos.setY(pos.getY() + dir.getY() * VELOCITYB);
}


void Bow::handleEvents() {


}