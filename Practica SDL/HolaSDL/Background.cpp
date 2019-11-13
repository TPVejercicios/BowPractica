#include "Background.h"

Background::Background(Point2D _pos, int _h, int _w, int _angle, int _scale, Texture* _texture, Game* _game) :
	ArrowGameObject(_pos, _h, _w, _angle, _scale, _texture, _game) {}

Background::~Background() {

}
