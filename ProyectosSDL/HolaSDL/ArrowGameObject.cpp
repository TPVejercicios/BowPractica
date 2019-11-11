#include "ArrowGameObject.h"


ArrowGameObject::ArrowGameObject(Point2D _pos, Vector2D _angle, Vector2D _scale, Texture* _texture, SDL_Rect* _body) {
	pos = _pos;
	angle = _angle;
	scale = _scale;
	texture = _texture;
	body = _body;
}

ArrowGameObject::~ArrowGameObject() {

}

void ArrowGameObject::render() const {
	texture->render(*body, SDL_FLIP_NONE);
}

void ArrowGameObject::update() {

}