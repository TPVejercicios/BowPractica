#include "Ballon.h"
#include "Game.h"


Ballon::Ballon(Point2D _pos, Vector2D _dir, int _h, int _w, int _angle, int _scale, Texture* _texture, Game* _game,int _speed, int _id) :
	ArrowGameObject(_pos, _dir, _h, _w, _angle, _scale, _texture, _game,_id) {
	ballonSpeed = _speed;
	currRow = rand() % ROWS;
}

void Ballon::update() {

	if (currStatus == SWOLLEN) {
		pos.setY(pos.getY() - (dir.getY() * ballonSpeed));
		if (pos.getY() < TOP_LIMIT) {
			currStatus = PUNCTURED;
		}
	}
	else
	{
		currColl++;
		if (currColl > texture->getNumCols() && !deleting) {
			deleting = true;
			game->killObject(this);
		}
	}
}

void Ballon::startDestruction() {
	collisionable = false;
	dir.setY(0);
	currStatus = PUNCTURED;
}

