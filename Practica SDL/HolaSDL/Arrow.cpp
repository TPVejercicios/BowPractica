#include "Arrow.h"
#include "Game.h"




void Arrow::update() {
	pos.setX(pos.getX() + dir.getX() * ARROW_SPEED);
	if (pos.getX() > WIN_HEIGHT ) {
		game->killObject(this);
	}
}

