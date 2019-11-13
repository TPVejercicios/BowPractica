#include "Background.h"

Background::Background(int _h, int _w, Texture* _texture){
	h = _h;
	w = _w;
	texture = _texture;
}

Background::~Background() {
	texture = nullptr;
}

void Background::render() const {
	texture->render({0, 0, w, h}, SDL_FLIP_NONE);
}

void Background::changeBackground(Texture* _texture) {
	texture = _texture;
}