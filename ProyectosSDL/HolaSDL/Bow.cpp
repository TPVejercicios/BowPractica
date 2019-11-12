#include "Bow.h"
#include "Arrow.h"
#include "Texture.h"
#include "Game.h"
#include <iostream>

//Constructora de bow
Bow::Bow(Texture* _bowCharged,Texture*_bowDiscarged,Texture* _arrowSprite, Game* _game)
	:ArrowGameObject(_game), EventHandler()
{
	currBow = bowCharged = _bowCharged;
	bowDischarged = _bowDiscarged;
	arrowSprite = _arrowSprite;
	remainingShots = START_ARROWS;
	scale = 4;
	body->h = currBow->getH() / scale;
	body->w = currBow->getW() / scale;
	body->x = pos.getX();
	body->y = pos.getY();
}

//Destructora de bow
Bow::~Bow() {
	try {
		for (int i = 0; i < quiver.size(); i++) delete quiver.at(i);
		quiver.clear();
		arrowSprite = nullptr;
		currBow = nullptr;
		bowCharged = nullptr;
		bowDischarged = nullptr;
		cout << "Se ha destruido el bow" << endl;
	}
	catch (exception e) {
		cout << "Error deleting a bow" << e.what() << endl;
	}
}

//Renderiza el bow 
void Bow::render() const {
	currBow->render(*body, SDL_FLIP_NONE);
	if (!quiver.empty()) {
		for (int i = 0; i < quiver.size(); i++) {
			quiver.at(i)->render();
		}
	}
}

//Falta borrar una flecha que se ha salido de la pantalla
//Actualiza la posición del bow y lo limita para que no se salga de la escena
void Bow::update() {
	pos.setY(pos.getY() + dir.getY() * BOW_SPEED);
	if (pos.getY() < 0) {
		pos.setY(0);
	}
	else if (pos.getY() > (WIN_HEIGHT - currBow->getH()) / SCALE_DIV) {
		pos.setY(WIN_HEIGHT - currBow->getH() / SCALE_DIV);
	}
	body->y = pos.getY();
	if (!quiver.empty()) {
		for (int i = 0; i < quiver.size(); i++) {
			quiver.at(i)->update();
			/*if () {
			//Meter objeto a  la lista de killObject
				delete quiver.at(i);
				quiver.erase(quiver.begin() + i);
			}*/
		}
	}
}

//Controla el input para mover el arco en el eje Y
void Bow::handleEvent(const SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		//Tecla abajo
		if (event.key.keysym.sym == SDLK_DOWN) dir.setY(1); 
		//Tecla ariba
		else if (event.key.keysym.sym == SDLK_UP) dir.setY(-1);
		//Tecla disparo
		else if (event.key.keysym.sym == SDLK_RIGHT && charged) {	
			charged = false;
			body->x = pos.getX() + gap;
			body->w = bowDischarged->getW() / SCALE_DIV;
			currBow = bowDischarged;
			Vector2D shootPos;
			shootPos.setX(pos.getX());
			shootPos.setY(pos.getY() + (body->h / 2) - 6);
			game->shootArrow(shootPos);
			game->bowShoted();
		}
		//Tecla recarga
		else if (event.key.keysym.sym == SDLK_LEFT && !charged && remainingShots > 0) {	
			remainingShots--;
			body->x = pos.getX();
			body->w = bowCharged->getH() / SCALE_DIV;
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

