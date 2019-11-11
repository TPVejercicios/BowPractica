#pragma once
#include <vector>
#include "ArrowGameObject.h"
#include "Arrow.h"
#include "EventHandler.h"

class Game;


using namespace std;
using Point2D = Vector2D;						
const int START_ARROWS = 10;							//Cantidad de arrows con las que se inicia el juego
const int BOW_SPEED = 20;								//Velocidad de movimiento del bow

//La clase Bow es hija de ArrowGameObject y tambi�n de EventHandler
class Bow : public ArrowGameObject{
private:
	int	gap = 31;								//Desface gr�fico que hay entre el bow cargado y el descargado
	int	remainingShots;							//Variable que lleva la cuenta de las arrows que quedan
	bool charged = true;				//Variable que determina si el bow est� cargado
	vector<Arrow*> arrows;				//Vector de punteros de arrows

public:
	Bow() {};
	Bow(Texture* _texture);
	~Bow();
	void update();
	void handleEvents(const SDL_Event event);		
	void render();
	//M�todos de arrow
	bool bowShoted() { return arrows.empty() ? false : true; };
	SDL_Rect* returnArrowHeadBow(int i) { return arrows.empty() ? nullptr : arrows.at(i)->returnArrowHead(); };
	int arrowShooted() { return arrows.size(); };
	int arrowsLeft() { return remainingShots; };
};