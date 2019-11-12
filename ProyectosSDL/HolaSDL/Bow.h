#pragma once
#include "ArrowGameObject.h"
#include "EventHandler.h"
#include "Arrow.h"

class Game;
using namespace std;					
const int START_ARROWS = 10;							//Cantidad de arrows con las que se inicia el juego
const int BOW_SPEED = 20;								//Velocidad de movimiento del bow

//La clase Bow es hija de ArrowGameObject y también de EventHandler
class Bow : public ArrowGameObject, public EventHandler{
private:
	Texture* currBow = nullptr;
	Texture* bowDischarged = nullptr;
	Texture* bowCharged = nullptr;
	Texture* arrowSprite = nullptr;
	int	gap = 31;								//Desface gráfico que hay entre el bow cargado y el descargado
	int	remainingShots = 0;						//Variable que lleva la cuenta de las arrows que quedan
	bool charged = true;						//Variable que determina si el bow está cargado
	vector <Arrow*> quiver;						//Vector de punteros de arrows

public:

	Bow() : ArrowGameObject() {};
	Bow(Texture* _bowCharged, Texture* _bowDiscarged,Texture* _arrowSprite, Game* _game);
	~Bow();
	//Métodos genéricos
	virtual void update();//handleEvent
	virtual void handleEvent(const SDL_Event event);
	virtual void render() const;
	//Métodos de arrow
	bool bowShoted() { return quiver.empty() ? false : true; };
	//SDL_Rect* returnArrowHeadBow(int i) { return arrows.empty() ? nullptr : arrows.at(i).returnArrowHead(); };
	int arrowShooted() { return quiver.size(); };
	int arrowsLeft() { return remainingShots; };
};