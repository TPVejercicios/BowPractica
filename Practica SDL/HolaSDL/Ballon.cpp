#include "Ballon.h"
#include "Game.h"


Ballon::Ballon(Point2D _pos, Vector2D _dir, int _h, int _w, int _angle, int _scale, Texture* _texture, Game* _game,int _speed) :
	ArrowGameObject(_pos, _dir, _h, _w, _angle, _scale, _texture, _game, ID) {
	ballonSpeed = _speed;
	currCol = rand() % texture->getNumCols() + 1;
}


Ballon::~Ballon() {

}

void Ballon::update() {
	pos.setY(pos.getY() - (dir.getY() * ballonSpeed));
	if (pos.getY() < TOP_LIMIT) {
		game->killObject(this);
	}
}

