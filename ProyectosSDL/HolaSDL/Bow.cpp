#include "Bow.h"
#include "Game.h"
#include <iostream>

//Constructora de bow
Bow::Bow(Texture* bowChar, Texture* bowDisChar, Texture* arrowSprite) {
	pos.setX(0);
	pos.setY(0);
	dir.setX(0);
	dir.setY(0);
	ArrowGameObject()
	arrowTexture = arrowSprite;
	remainingShots = START_ARROWS;
	bowCharged = currBow =  bowChar;
	bowDischarged = bowDisChar;
	pos.setX(0);
	pos.setY(0);
	dir.setX(0);
	dir.setY(0);
	//Rect del arco para renderizar 
	bodyBow = new SDL_Rect();
	bodyBow->h = bowCharged->getH() / SCALE_DIV;
	bodyBow->w = bowCharged->getW() / SCALE_DIV;
	bodyBow->x = pos.getX();
	bodyBow->y = pos.getY();
}

//Destructora de bow
Bow::~Bow() {
	try {

		for (int i = 0; i < quiver.size(); i++) delete quiver.at(i);

		quiver.clear();
		arrowTexture = nullptr;
		currBow = nullptr;
		bowCharged = nullptr;
		bowDischarged = nullptr;
		delete bodyBow;
		cout << "Se ha destruido el bow" << endl;
	}
	catch (exception e) {
		cout << "Error deleting a bow" << e.what() << endl;
	}

}

//Renderiza el bow 
void Bow::render() {
	currBow->render(*bodyBow,SDL_FLIP_NONE);
	if (!quiver.empty()) {
		for (int i = 0; i < quiver.size(); i++) {
			quiver.at(i)->render();
		}
	}
}

//Actualiza la posición del bow y lo limita para que no se salga de la escena
void Bow::update() {
	pos.setY(pos.getY() + dir.getY() * BOW_SPEED);
	if (pos.getY() < 0) {
		pos.setY(0);
	}
	else if (pos.getY() > WIN_HEIGHT - currBow->getH() / SCALE_DIV) {
		pos.setY(WIN_HEIGHT - currBow->getH() / SCALE_DIV);
	}
	bodyBow->y = pos.getY();
	if (!quiver.empty()) {
		for (int i = 0; i < quiver.size(); i++) {
			if (quiver.at(i)->update()) {
				delete quiver.at(i);
				quiver.erase(quiver.begin() + i);
			}
		}
	}
}

//Controla el input para mover el arco en el eje Y
void Bow::handleEvents(const SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		//Tecla abajo
		if (event.key.keysym.sym == SDLK_DOWN) dir.setY(1); 
		//Tecla ariba
		else if (event.key.keysym.sym == SDLK_UP) dir.setY(-1);
		//Tecla disparo
		else if (event.key.keysym.sym == SDLK_RIGHT && charged) {	
			charged = false;
			bodyBow->x = pos.getX() + gap;
			bodyBow->w = bowDischarged->getW() / SCALE_DIV;
			currBow = bowDischarged;
			Arrow* currArrow = new Arrow(arrowTexture);
			quiver.push_back(currArrow);
			currArrow = nullptr;
			Vector2D shootPos;
			shootPos.setX(pos.getX());
			shootPos.setY(pos.getY() + (bodyBow->h / 2) - 6);
			quiver.back()->shootArrow(shootPos);
		}
		//Tecla recarga
		else if (event.key.keysym.sym == SDLK_LEFT && !charged && remainingShots > 0) {	
			remainingShots--;
			bodyBow->x = pos.getX();
			bodyBow->w = bowCharged->getH() / SCALE_DIV;
			currBow = bowCharged;
			charged = true;
		}
		//Para testeo, aumenta la cantidad de flechas para disparar en 100
		else if (event.key.keysym.sym == SDLK_p) {
			remainingShots += 100;
		}
	}
	else {
		dir.setY(0);
	}

}