#pragma once
#include "ArrowGameObject.h"

class Game;
class Texture;

class Background : public ArrowGameObject {
private:
	Texture* texture = nullptr;

public:
	Background();
	Background(Texture* _texture, Game* _game);
	~Background();
	void render() const;
};

