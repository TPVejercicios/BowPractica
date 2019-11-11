#pragma once
#include "ArrowGameObject.h"
class Game;


using namespace std;
using Point2D = Vector2D;
const int MAX_BALLON_SPEED = 5;			//Velocidad de movimiento del ballon

enum punctured
{
	PUNCTURED = 0,						//Pinchado
	SWOLLEN = 1							//Hinchado
};

//La clase Ballon hereda de ArrowGameObject
class Ballon : public ArrowGameObject {
private:
	Point2D		pos;					//Posición del ballon en el eje x e y
	Vector2D	vel;					//Dirección del ballon
	uint		timePunctured;			//El tiempo en el que el ballon es pinchado
	int			numTexture, numBallon, collFrame = 0, gap = 10;
	punctured	status		= SWOLLEN;	//Enum que representa el estado del ballon
	Texture*	texture		= nullptr;	//Textura del ballon
	Game*		game		= nullptr;	//Puntero a game
	SDL_Rect*	ballonBody	= nullptr;	//Rect dele ballon para renderizar y controlar colisiones
public:
	Ballon(Texture* ballonSprite, Point2D _pos, Vector2D _angle, Vector2D _scale, Game* _game, Texture* _texture, SDL_Rect* _body) 
		:ArrowGameObject(_pos, _angle, _scale, _game, _texture, _body),texture(ballonSprite) {};

	~Ballon();
	void update();
	void render() const;
	//cambia el estado del globo para empezar la animación de rotura
	void ballonPunctured() { status = PUNCTURED; };	
	//Devuelve el Rect del ballon
	SDL_Rect* returnBallonBody() { return ballonBody; };
	//Devuelve true si el globo está inflado 
	bool returnState() { return status == SWOLLEN ? true : false; };
};

