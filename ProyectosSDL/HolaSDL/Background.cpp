#include "Background.h"
#include "Texture.h"

Background::Background() : ArrowGameObject() { }

Background::Background(Texture* _texture, Game* _game) : ArrowGameObject(_game), texture(_texture) { body = nullptr; }

Background::~Background() {}

void Background::render() const { texture->render(*body, SDL_FLIP_NONE); }
