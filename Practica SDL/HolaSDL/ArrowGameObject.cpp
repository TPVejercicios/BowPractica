#include "ArrowGameObject.h"

ArrowGameObject::ArrowGameObject(Point2D _pos, Vector2D _dir, int _h, int _w, int _angle, int _scale, Texture* _texture, Game* _game,int _id){
	pos = _pos;
	dir = _dir;
	h = _h;
	w = _w;
	angle = _angle;
	scale = _scale;
	texture = _texture;
	game = _game;
	objectID = _id;
}

ArrowGameObject::~ArrowGameObject() {
	texture = nullptr;
	game = nullptr;
}

