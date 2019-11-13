#include "Bow.h"

Bow::Bow(Point2D _pos, int _h, int _w, int _angle, int _scale, Texture* _texture, Game* _game, Vector2D _dir, int _remainingShots) :
	ArrowGameObject(_pos, _h, _w, _angle, _scale, _texture, _game) {
	dir = _dir;
	remainingShots = _remainingShots;
}

Bow::~Bow() {

}

void Bow::update() {
	pos.setY(pos.getY() + dir.getY() * BOW_SPEED);
	if (pos.getY() < 0) pos.setY(0);
	if (pos.getY() > 600 - h) pos.setY(600 - h); //Ese 600 tendría que ser la variable globar WIN_HEIGHT
}

void Bow::handleEvents(const SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		//Tecla abajo
		if (event.key.keysym.sym == SDLK_DOWN) dir.setY(1); 
		//Tecla ariba
		else if (event.key.keysym.sym == SDLK_UP) dir.setY(-1);
		//Tecla disparo
		else if (event.key.keysym.sym == SDLK_RIGHT && charged) {	

			charged = false;
		}
		//Tecla recarga
		else if (event.key.keysym.sym == SDLK_LEFT && !charged && remainingShots > 0) {	

			charged = true;
		}
	}
	else {
		dir.setY(0);
	}
}

