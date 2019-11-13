#include "ArrowGameObject.h"

ArrowGameObject::ArrowGameObject(Point2D _pos, int _h, int _w, int _angle, int _scale, Texture* _texture, Game* _game){
	pos = _pos;
	h = _h;
	w = _w;
	angle = _angle;
	scale = _scale;
	texture = _texture;
	game = _game;
}

ArrowGameObject::~ArrowGameObject() {
	texture = nullptr;
	game = nullptr;
}

void ArrowGameObject::render() const {
	texture->render(getRect(), SDL_FLIP_NONE);
}

SDL_Rect ArrowGameObject::getRect() const {
	SDL_Rect rect;
	rect.h = h;
	rect.w = w;
	rect.x = pos.getX();
	rect.y = pos.getY();
	return rect;
}