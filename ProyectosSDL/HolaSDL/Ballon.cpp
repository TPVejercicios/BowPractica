#include "Ballon.h"
#include <iostream>
#include "Game.h"

using namespace std;

Ballon::~Ballon() {
	texture = nullptr;
	game = nullptr;
	ballonBody = nullptr;
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
	ballonBody->h = 80;
	ballonBody->w = 80;
	ballonBody->x = pos.getX() + 10;
	ballonBody->y = pos.getY() + 10;
}

//Renderiza el globo
void Ballon::render(SDL_Renderer* renderer) const {
	SDL_Rect des;
	des.h = 100;
	des.w = 100;
	des.x = pos.getX();
	des.y = pos.getY();
	texture->renderFrame(des, numTexture,collFrame,1,SDL_FLIP_NONE);
}

//Mueve el globo en función de su velocidad
bool Ballon::update() {
	bool destroy = false;
	if (status == SWOLLEN) {
		ballonBody->x = pos.getX() + 10;
		ballonBody->y = pos.getY() + 10;
		pos.restaVectorEnY(vel);
		game->checkCrushBallon();
		if (pos.getY() < -100) {
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

//cambia el estado del globo para empezar la animación de rotura
void Ballon::ballonPunctured(uint time) {
	uint animTime = 1000;
	cout << "Globo pinchado" << endl;
	status = PUNCTURED;
	timePunctured = time;
	//empezar animacion 
}




