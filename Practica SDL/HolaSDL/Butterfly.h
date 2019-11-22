#pragma once
#include "ArrowGameObject.h"

const uint MIN_X = 300;
const uint MAX_X = 750;
const uint MAX_Y = 550;
const int MAX_SPEED = 2;

class Butterfly : public ArrowGameObject
{
private:
	SDL_RendererFlip flip = SDL_FLIP_NONE;
public:
	Butterfly(Point2D _pos, Vector2D _dir, int _h, int _w, int _angle, int _scale, Texture* _texture, Game* _game, int _id) :
		ArrowGameObject(_pos, _dir, _h, _w, _angle, _scale, _texture, _game, _id) {
	}
	virtual void update();
	virtual void render() const;
};

