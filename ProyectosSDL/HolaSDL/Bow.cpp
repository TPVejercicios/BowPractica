#include "Bow.h"
#include "Game.h"

//Constructora de bow
Bow::Bow(Texture* t1, Texture* t2, int r) {
	tirosRestantes = r - 1;
	textureC = t1;
	textureD = t2;
	pos.setX(0);
	pos.setY(0);
	dir.setX(0);
	dir.setY(0);
	bodyBow = new SDL_Rect();
	bodyBow->h = y;
	bodyBow->w = xC;
	bodyBow->x = pos.getX();
	bodyBow->y = pos.getY();
}

//Destructora de bow
Bow::~Bow() {
	textureC->liberar();
	textureD->liberar();
	delete bodyBow;
}

//Renderiza el bow 
void Bow::render() const {	
	bodyBow->h = y;
	if (cargado) {
		bodyBow->x = pos.getX();
		bodyBow->w = xC;
		textureC->render(*bodyBow, SDL_FLIP_NONE);
	}
	else
	{
		bodyBow->x = pos.getX() + dist;
		bodyBow->w = xD;
		textureD->render(*bodyBow, SDL_FLIP_NONE);
	}
	/*SDL_Rect* des = new SDL_Rect();
	des->h = y;
	des->y = pos.getY();
	des->y = pos.getY();
	if (cargado) {
		des->x = pos.getX();
		des->w = xC;
		bodyBow->w = xC;
		textureC->render(*bodyBow,SDL_FLIP_NONE);
		//SDL_RenderCopy(renderer, textureC->getTexture(), nullptr, des); // Copia en buffer
	}
	else {
		des->x = pos.getX() + dist;
		bodyBow->x = pos.getX() + dist;
		bodyBow->w = xD;
		des->w = xD;
		textureD->render(*bodyBow, SDL_FLIP_NONE);
		//SDL_RenderCopy(renderer, textureD->getTexture(), nullptr, des); // Copia en buffer
	}
	delete des;*/
}

//Actualiza la posición del bow y lo limita para que no se salga de la escena
void Bow::update() {
	pos.setY(pos.getY() + dir.getY() * VELOCITYB);
	if (pos.getY() < 0) {
		pos.setY(0);
	}
	else if (pos.getY() > WIN_HEIGHT - y) {
		pos.setY(WIN_HEIGHT - y);
	}
	bodyBow->y = pos.getY();
}

//Controla el input para mover el arco en el eje Y
void Bow::handleEvents(const SDL_Event event) {
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
		else if (event.key.keysym.sym == SDLK_LEFT && !cargado && tirosRestantes > 0) {	//Tecla disparo
			cargado = true;
			tirosRestantes--;
		}
	}
	else {
		dir.setY(0);
	}

}