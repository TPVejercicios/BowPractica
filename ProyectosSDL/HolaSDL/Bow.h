#pragma once
#include "Texture.h"
#include "Vector2D.h"
#include "Arrow.h"
#include <vector>

class Game;

using namespace std;
using Point2D = Vector2D;
using Quiver = vector<Arrow*>;						
const int START_ARROWS = 10;							//Cantidad de arrows con las que se inicia el juego
const int BOW_SPEED = 20;								//Velocidad de movimiento del bow


class Bow {
private:
	int			gap = 31;								//Desface gráfico que hay entre el bow cargado y el descargado
	int			remainingShots;							//Variable que lleva la cuenta de las arrows que quedan
	bool		charged			= true;					//Variable que determina si el bow está cargado
	Vector2D	dir;									//Direccion del arco
	Point2D		pos;									//Esquina superior izquierda
	Texture*	arrowTexture	= nullptr;				//Textura del arrow
	Texture*	bowCharged		= nullptr;				//Textura del bow cargado
	Texture*	bowDischarged	= nullptr;				//Textura del bow descargado
	Texture*	currBow			= nullptr;				//Textura del bow que uso
	SDL_Rect*	bodyBow			= nullptr;				//Rect de bow para renderizar
	Quiver		quiver;									//Vector de punteros de arrows

public:
	Bow(Texture* bowCharged, Texture* bowDischarger, Texture* arrowSprite);
	~Bow();
	void update();
	void handleEvents(const SDL_Event event);		
	void render();
	//Métodos de arrow
	bool bowShoted() { return quiver.empty() ? false : true; };
	SDL_Rect* returnArrowHeadBow(int i) { return quiver.empty() ? nullptr : quiver.at(i)->returnArrowHead(); };
	int arrowShooted() { return quiver.size(); };
	int arrowsLeft() { return remainingShots; };
};