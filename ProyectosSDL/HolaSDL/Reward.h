#pragma once
#include "ArrowGameObject.h"
#include "EventHandler.h"

class Game;
class Vector2D;
class Texture;
class SDL_Rect;
using Point2D = Vector2D;


//La clase Reward es hija de ArrowGameObject y también de EventHandler
class Reward : public ArrowGameObject, public EventHandler {
private:

public:
	Reward(Point2D _pos, Vector2D _angle, Vector2D _scale, Game* _game, Texture* _texture, SDL_Rect* _body);

};

