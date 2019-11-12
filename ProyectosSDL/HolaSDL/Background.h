#pragma once
#include "ArrowGameObject.h"
class Game;
class Background : public ArrowGameObject {
private:
	Texture* texture = nullptr;

public:
	Background() : ArrowGameObject() { };
	Background(Texture* _texture, Game* _game) :ArrowGameObject(_game), texture(_texture) { body = nullptr; };
	~Background() {};
	void render() const { texture->render(*body,SDL_FLIP_NONE); };
};

