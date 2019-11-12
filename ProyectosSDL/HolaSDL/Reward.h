#pragma once
#include "ArrowGameObject.h"
#include "EventHandler.h"

class Texture;

//La clase Reward es hija de ArrowGameObject y también de EventHandler
class Reward : public ArrowGameObject, public EventHandler {
private:

public:
	Reward(Texture* _texture, Game* _game);

};

