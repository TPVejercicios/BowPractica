#include "Arrow.h"
#include "Game.h"
#include <iostream>

void Arrow::update() {
	pos.setX(pos.getX() + dir.getX() * ARROW_SPEED);
	if (pos.getX() > WIN_HEIGHT + 200 && !deleting ) {
		deleting = true;
		game->arrowStacks(ballonsPunctured);
		game->killObject(this);
	}
}

