#include "ArrowGameObject.h"


ArrowGameObject::ArrowGameObject(Point2D _pos, Vector2D _angle, Vector2D _scale, Game* _game) {
	pos = _pos;
	angle = _angle;
	scale = _scale;
	game = _game;
}

ArrowGameObject::~ArrowGameObject() {

}
void ArrowGameObject::render() const {

}

void ArrowGameObject::update() {

}