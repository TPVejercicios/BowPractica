#include "Bow.h"
#include "Game.h"

//Constructora de bow
Bow::Bow(Texture* t1, Texture* t2, Texture* t3, Texture* t4, int r) {
	r--;
	arrow = new Arrow(t3, t4, r,this);
	tirosRestantes = r;
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
	delete arrow;
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
	arrow->render();
	arrow->renderHUD();
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
	arrow->update();
}

//Controla el input para mover el arco en el eje Y
void Bow::handleEvents(const SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_DOWN) {	//Tecla abajo
			dir.setY(1);
			if(!arrow->getDisparada()) arrow->setDirection(0, 1); //La flecha solo se mueve para abajo si no esta disparada
		}
		else if (event.key.keysym.sym == SDLK_UP) {	//Tecla ariba
			dir.setY(-1);
			if (!arrow->getDisparada()) arrow->setDirection(0, -1);
		}
		else if (event.key.keysym.sym == SDLK_RIGHT) {	//Tecla disparo
			cargado = false;
			arrow->setDirection(1, 0);
		}
		else if (event.key.keysym.sym == SDLK_LEFT && !cargado && tirosRestantes > 0) {	//Tecla disparo
			arrow->setDirection(0, 0);
			cargado = true;
			tirosRestantes--;
		}
	}
	else {
		dir.setY(0);
		arrow->setDirection(0, 0);
	}

}