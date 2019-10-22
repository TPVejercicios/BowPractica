#include "Bow.h"

void Bow::render() const {
	SDL_Rect* pos =  new SDL_Rect();
	pos->x = pos->y = 100;
	texture->render(pos,SDL_Flip);//AQUI ME QUEDé
}

void Bow::update() {

}


void Bow::handleEvents() {


}