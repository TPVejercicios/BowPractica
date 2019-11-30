#pragma once
#include "ArrowGameObject.h"

const int ARROW_SPEED = 25;
const int H_FOR_COLLISION = 5;
const int W_FOR_COLLISION = 50;
const int GAP_COll = 55;

class Arrow : public ArrowGameObject
{
private:
	int ballonsPunctured = 0;

public: 
	Arrow(Point2D _pos, Vector2D _dir, int _h, int _w, int _angle, int _scale, Texture* _texture, Game* _game,int _id) :
		ArrowGameObject(_pos, _dir, _h, _w, _angle, _scale, _texture, _game,_id) {
	}
	~Arrow() {};
	virtual void update();
	virtual void saveToFile(string& data);
	void AddStack() { ballonsPunctured += 1; };
	SDL_Rect getRectForCollision() const { return{ pos.getX() + GAP_COll,pos.getY(),W_FOR_COLLISION,H_FOR_COLLISION }; }
};

