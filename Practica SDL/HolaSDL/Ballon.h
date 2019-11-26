#pragma once
#include "ArrowGameObject.h"

int const TOP_LIMIT = -200;

int const ROWS = 7;
enum status
{
	SWOLLEN, PUNCTURED
};


class Ballon : public ArrowGameObject
{
private :
	int ballonSpeed = 0;
	int currRow = 0;					//Determina el color del globo
	int currColl = 0;
	status currStatus = SWOLLEN;
public:
	Ballon() {};
	Ballon(Point2D _pos, Vector2D _dir, int _h, int _w, int _angle, int _scale, Texture* _texture, Game* _game,int _speed,int _id);
	virtual void update();
	virtual void render() const { texture->renderFrame(getRect(),currRow,currColl,SDL_FLIP_NONE); };
	virtual void startDestruction();
};

