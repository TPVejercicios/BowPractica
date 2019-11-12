#pragma once
#include "ArrowGameObject.h"

class Game;
class Texture;
using Point2D = Vector2D;
const int ARROW_SPEED = 20;				//Velocidad de movimiento de arrow

//La clase Arrow hereda de ArrowGameObject
class Arrow : public ArrowGameObject {
private:
	Point2D		pos;					//Posici�n en el eje x e y
	int disT =	44;						//Valor de centrado de la flecha con respecto al arco
	int gap	 =	55;						//Distancia para coger el rect de la cabeza de la flecha
	Vector2D	dir;					//Vector direcci�n del disparo
	Texture*	texture = nullptr;		//Textura de arrow
	bool		shooted = false;		//Determina si el arrow est� siedo disparada

public:
	//Constructor
	Arrow() :ArrowGameObject() {};
	Arrow(Texture* arrowSprite,Vector2D _pos, Game* _game);
	//Destructor
	~Arrow();
	//M�todos genericos
	void update();
	void render();
	bool killArrow() {};
};