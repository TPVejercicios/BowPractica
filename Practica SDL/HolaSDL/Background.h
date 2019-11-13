#pragma once
#include <vector>
#include "ArrowGameObject.h"

class Game;

using namespace std;
using Point2D = Vector2D;

//La clase Background es hija de ArrowGameObject
class Background : public ArrowGameObject {
private:
public:
	Background() {};
	Background(Point2D _pos, int _h, int _w, int _angle, int _scale, Texture* _texture, Game* _game);
	~Background();
	virtual void render();
};