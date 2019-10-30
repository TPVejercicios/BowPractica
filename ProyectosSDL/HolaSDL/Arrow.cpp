#include "Arrow.h"
#include "Bow.h"
#include "Game.h"

Arrow::~Arrow() {
	texture->liberar();
	texture2->liberar();
	delete arrowHead;
	delete arrowFull;
}

//Crea una flecha
Arrow::Arrow(Texture* t, Texture* t2, int r,Bow* b) {
	bow = b;
	restantes = r;
	pos.setX(0);
	pos.setY(disT);
	dir.setX(1);
	dir.setY(0);
	texture = t;
	texture2 = t2;
	//El rect de la flecha entera para dibujarla
	arrowFull = new SDL_Rect();
	arrowFull->x = pos.getX();
	arrowFull->y = pos.getY();
	arrowFull->w = x;
	arrowFull->h = y;
	//El rect de la punta de la flecha, evitando el palo para detectar las colisiones
	arrowHead = new SDL_Rect();
	arrowHead->h = y;
	arrowHead->w = x/5;
	arrowHead->x = pos.getX() + 80;
	arrowHead->y = pos.getY();
	//El rect de las flechas del HUD
	arrowHUD = new SDL_Rect();
	arrowHUD->y = hudY;
	arrowHUD->w = hudW;
	arrowHUD->h = hudH;
	arrowHUD->x = hudX;
};

//Renderiza una flecha en movimiento
void Arrow::render() const {
	if (disparada) {
		texture->render(*arrowFull, SDL_FLIP_NONE);
	}
}

//Renderiza las flechas que aparecen en el HUD OSCAR hay que usar el metodo render de texture
void Arrow::renderHUD() const {
	for (int i = 0; i < restantes; i++) {
		arrowHUD->x = hudX + i * 10;
		texture2->render(*arrowHUD, SDL_FLIP_NONE);
	}
	arrowHUD->x = hudX;
}

//Actualiza la posición de la flecha mientras viaja
void Arrow::update() {		
	arrowFull->x = pos.getX();
	arrowFull->y = pos.getY();
	arrowHead->x = pos.getX() + gap;
	arrowHead->y = pos.getY();

	if (!disparada) {
		pos.setY(pos.getY() + dir.getY() * VELOCITYC);
		if (pos.getY() < disT) {
			pos.setY(disT);
		}
		else if (pos.getY() > WIN_HEIGHT - y - disD) {
			pos.setY(WIN_HEIGHT - y - disD);
		}
	}
	if (disparada && pos.getX() < WIN_WIDTH) {				
		pos.setX(pos.getX() + dir.getX() * VELOCITYA);
	}
	else if (pos.getX() <= WIN_WIDTH) {
		finDisparo = true;
	}
}

void Arrow::setDirection(int x, int y) {
	dir.setX(x);
	dir.setY(y);
}


//Comprueba las flechas que quedan y recarga si es posible
void Arrow::recargar(const int posYArco) {
	if (restantes > 0) {
		finDisparo = false;
		disparada = false;
		pos.setX(0);
		pos.setY(posYArco + disT);		//Obtener de alguna forma la posicion del arco
		restantes--;
	}
}