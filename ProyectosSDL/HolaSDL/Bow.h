#pragma once
#include "Texture.h"
#include "Vector2D.h"
#include "Arrow.h"
#include <vector>
#include "ArrowGameObject.h"

class Game;

using namespace std;
using Point2D = Vector2D;
using Quiver = vector<Arrow*>;						
const int START_ARROWS = 10;							//Cantidad de arrows con las que se inicia el juego
const int BOW_SPEED = 20;								//Velocidad de movimiento del bow


class Bow : public ArrowGameObject {
private:
	int			gap = 31;								//Desface gráfico que hay entre el bow cargado y el descargado
	int			remainingShots;							//Variable que lleva la cuenta de las arrows que quedan
	bool		charged			= true;					//Variable que determina si el bow está cargado	
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