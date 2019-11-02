#pragma once
#include "Texture.h"
#include "Vector2D.h"
class Game;

using Point2D = Vector2D;
const int ARROW_SPEED = 20;				//Velocidad de movimiento de arrow

class Arrow
{
private:
	Point2D		pos;					//Posici�n en el eje x e y
	int disT =	44;						//Valor de centrado de la flecha con respecto al arco
	int gap	 =	55;						//Distancia para coger el rect de la cabeza de la flecha
	Vector2D	dir;					//Vector direcci�n del disparo
	Texture*	texture = nullptr;		//Textura de arrow
	SDL_Rect*	arrowFull = nullptr;	//Rect de arrow en su totalidad
	SDL_Rect*	arrowHead = nullptr;	//Rect de arrow reducido para controlar colisiones
	bool		shooted = false;		//Determina si el arrow est� siedo disparada

public:
	Arrow(Texture* arrowSpite);
	~Arrow();
	bool update();
	void render();
	SDL_Rect* returnArrowHead() { return arrowHead; };
	void shootArrow(Vector2D shootPos);
};