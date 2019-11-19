#pragma once
#include "ArrowGameObject.h"

int const TOP_LIMIT = -100;
int const ID = 004;

class Ballon : public ArrowGameObject
{
private :
	int ballonSpeed = 0;
	int currCol = 0;					//Determina el color del globo

public:
	Ballon() {};
	Ballon(Point2D _pos, Vector2D _dir, int _h, int _w, int _angle, int _scale, Texture* _texture, Game* _game,int _speed);
	~Ballon();
	virtual void update();
	virtual void render() const { texture->renderFrame(getRect(),currCol,0,SDL_FLIP_NONE); };
};

