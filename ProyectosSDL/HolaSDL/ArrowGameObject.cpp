#include "ArrowGameObject.h"


ArrowGameObject::ArrowGameObject(Point2D _pos, Vector2D _angle, Vector2D _scale, Game* _game, Texture* _texture, SDL_Rect* _body) : GameObject() {
	pos = _pos;
	angle = _angle;
	scale = _scale;
	game = _game;
	texture = _texture;
	body = _body;
}

ArrowGameObject::~ArrowGameObject() {

}
void ArrowGameObject::render() const {

}

void ArrowGameObject::update() {

}