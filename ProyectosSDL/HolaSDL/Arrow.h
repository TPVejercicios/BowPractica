#pragma once
#include "ArrowGameObject.h"

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
	SDL_Rect*	arrowFull = nullptr;	//Rect de arrow en su totalidad
	SDL_Rect*	arrowHead = nullptr;	//Rect de arrow reducido para controlar colisiones
	bool		shooted = false;		//Determina si el arrow est� siedo disparada

public:
	//Constructor
	//	ArrowGameObject(Point2D _pos, Vector2D _angle, Vector2D _scale, Game* _game, Texture* _texture, SDL_Rect* _body);

	Arrow(Texture* arrowSprite, Point2D _pos, Vector2D _angle, Vector2D _scale, Game* _game, Texture* _texture, SDL_Rect* _body)
		: ArrowGameObject(_pos, _angle, _scale, _game, _texture, _body), texture(arrowSprite) {};

		
	//Destructor
	~Arrow();
	//M�todos genericos
	void update();
	void render();
	//M�todos propios de la clase arrow
	SDL_Rect* returnArrowHead() { return arrowHead; };
	void shootArrow(Vector2D shootPos);
};