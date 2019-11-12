#pragma once
#include "ArrowGameObject.h"

class Game;
class Texture;
using Point2D = Vector2D;
const int ARROW_SPEED = 20;				//Velocidad de movimiento de arrow

//La clase Arrow hereda de ArrowGameObject
class Arrow : public ArrowGameObject {
private:
	Point2D		pos;					//Posición en el eje x e y
	int disT =	44;						//Valor de centrado de la flecha con respecto al arco
	int gap	 =	55;						//Distancia para coger el rect de la cabeza de la flecha
	Vector2D	dir;					//Vector dirección del disparo
	Texture*	texture = nullptr;		//Textura de arrow
	bool		shooted = false;		//Determina si el arrow está siedo disparada

public:
	//Constructor
	Arrow() :ArrowGameObject() {};
	Arrow(Texture* arrowSprite,Vector2D _pos, Game* _game);
	//Destructor
	~Arrow();
	//Métodos genericos
	void update();
	void render();
	bool killArrow() {};
};