#pragma once
#include "ArrowGameObject.h"


const uint MIN_X = 150;
const uint MAX_X = 750;
const uint MAX_Y = 550;
const int MAX_SPEED_BUT = 2;
const int DEAD_DIR = 1;
const int DEAD_SPEED = 10;

typedef enum 
{
	ALIVE = 0, DEAD = 1
}state_butterfly;

class Butterfly : public ArrowGameObject
{
private:
	state_butterfly currState = ALIVE;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	int currRow = 0;
	int currCol = 0;
public:
	Butterfly(Point2D _pos, Vector2D _dir, int _h, int _w, int _angle, int _scale, Texture* _texture, Game* _game, int _id) :
		ArrowGameObject(_pos, _dir, _h, _w, _angle, _scale, _texture, _game, _id) {
	}
	virtual void update();
	virtual void render() const;
	virtual void startDestruction();
};

