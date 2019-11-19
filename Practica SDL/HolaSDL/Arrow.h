#pragma once
#include "ArrowGameObject.h"

const uint ARROW_SPEED = 25;

class Arrow : public ArrowGameObject
{
private:
	int const ID = 002;
public: 
	Arrow(Point2D _pos, Vector2D _dir, int _h, int _w, int _angle, int _scale, Texture* _texture, Game* _game) :
		ArrowGameObject(_pos, _dir, _h, _w, _angle, _scale, _texture, _game,ID) {
	}
	~Arrow() {};
	virtual void update();
};

