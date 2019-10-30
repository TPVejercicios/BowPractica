#include "Ballon.h"
#include <iostream>
#include "Game.h"

using namespace std;

//Destructora de Ballon
Ballon::~Ballon() {
	texture = nullptr;
	game = nullptr;
	delete ballonBody;
}

//Genera un globo y pone valores aleatorios
Ballon::Ballon(Texture* t, Game* g) {
	int seed = rand() % 100;
	srand(seed);
	texture = t;
	pos.setX((rand()% (WIN_WIDTH/2)) + (WIN_WIDTH / 2) - 50);
	pos.setY(WIN_HEIGHT);
	vel.setX(0);
	vel.setY((rand() % (MAX_BALLON_SPEED + 1)) + 3);
	numTexture = rand() % (texture->getNumCols() + 1);
	game = g;
	ballonBody = new SDL_Rect();
	ballonBody->h = bodySize;
	ballonBody->w = bodySize;
	ballonBody->x = pos.getX() + gap;
	ballonBody->y = pos.getY() + gap;
}

//Renderiza el globo
void Ballon::render() const {
	texture->renderFrame(*ballonBody, numTexture,collFrame,1,SDL_FLIP_NONE);
}

//Mueve el globo en funci�n de su velocidad
bool Ballon::update() {
	bool destroy = false;
	if (status == SWOLLEN) {
		ballonBody->x = pos.getX() + gap;
		ballonBody->y = pos.getY() + gap;
		pos.subVectorInY(vel);
		game->checkCrushBallon();
		if (pos.getY() < -100) {		//Si el ballon sale por arriba 
			destroy = true;
		}
	}
	else
	{
		collFrame++;
		if (collFrame > texture->getNumCols()) {
			destroy = true;
		}
	}
	return destroy;

}
