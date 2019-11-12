#include "ArrowGameObject.h"
#include "Game.h"

ArrowGameObject::ArrowGameObject(Game* _game) {
	body = new SDL_Rect();
	collisionBody = new SDL_Rect();
	game = _game;
}

ArrowGameObject::~ArrowGameObject() {

}
