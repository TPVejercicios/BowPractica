#pragma once
#include "ArrowGameObject.h"
#include "SDL.h"

using namespace std;
class Game;
class Texture;
const int MAX_BALLON_SPEED = 5;			//Velocidad de movimiento del ballon

enum punctured
{
	PUNCTURED = 0,						//Pinchado
	SWOLLEN = 1							//Hinchado
};

//La clase Ballon hereda de ArrowGameObject
class Ballon : public ArrowGameObject {
private:
	uint32_t    timePunctured = 10;			//El tiempo en el que el ballon es pinchado
	int			numTexture = 0, numBallon = 0, collFrame = 0, gap = 10;
	punctured	status		= SWOLLEN;	//Enum que representa el estado del ballon
	Texture*	texture		= nullptr;	//Textura del ballon

public:
	Ballon() {};
	Ballon(Texture* ballonSprite, Game* _game);
	~Ballon();
	void update();
	void render() const;
	//cambia el estado del globo para empezar la animación de rotura
	void ballonPunctured() { status = PUNCTURED; };	

	//Devuelve true si el globo está inflado 
	bool returnState() { return status == SWOLLEN ? true : false; };
};

