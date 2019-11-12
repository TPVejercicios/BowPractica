#include "Arrow.h"
#include "Texture.h"
#include "Game.h"

using namespace std;

Arrow::~Arrow() {
	try {
		texture = nullptr;
		
		cout << "Flecha eliminada" << endl;
	}
	catch (exception e) {
		cout << "Error deleting an arrow" << e.what() << endl;
	}
}

Arrow::Arrow(Texture* arrowSprite,Vector2D _pos, Game* _game)
	: ArrowGameObject(_game)
{
	texture = arrowSprite;
	scale = 4;
	body->h = texture->getH() / scale;
	body->w = texture->getW() / scale;
	body->x = _pos.getX();
	body->y = _pos.getY();
	dir.setX(1);
	collisionBody->h = 5;
	collisionBody->w = texture->getW() / 100;
	collisionBody->x = pos.getX() + gap;
	collisionBody->y = pos.getY();
}

//Renderiza una flecha en movimiento
void Arrow::render() {
	if (shooted) texture->render(*body, SDL_FLIP_NONE);
}

//Actualiza la posición de la flecha mientras viaja
void Arrow::update() {
	pos.setX(pos.getX() + (dir.getX() * ARROW_SPEED));
	body->x = pos.getX();
	body->y = pos.getY();
	body->x = pos.getX() + gap;
	body->y = pos.getY();
	game->checkCrushBallon(collisionBody);
	if (pos.getX() > WIN_WIDTH) {
		game->addObjectToKill(this);
	}
}
