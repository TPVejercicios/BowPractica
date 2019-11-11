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

//La clase Reward es hija de ArrowGameObject y también de EventHandler
class Bow : public ArrowGameObject, public EventHandler {
private:
	int	gap = 31;								//Desface gráfico que hay entre el bow cargado y el descargado
	int	remainingShots;							//Variable que lleva la cuenta de las arrows que quedan
	bool charged = true;				//Variable que determina si el bow está cargado
	vector<Arrow*> arrows;				//Vector de punteros de arrows

public:
	Bow(Point2D _pos, Vector2D _angle, Vector2D _scale, Game* _game, Texture* _texture, SDL_Rect* _body);
	~Bow();
	void update();
	void handleEvents(const SDL_Event event);		
	void render();
	//Métodos de arrow
	bool bowShoted() { return arrows.empty() ? false : true; };
	SDL_Rect* returnArrowHeadBow(int i) { return arrows.empty() ? nullptr : arrows.at(i)->returnArrowHead(); };
	int arrowShooted() { return arrows.size(); };
	int arrowsLeft() { return remainingShots; };
};