#pragma once
#include <vector>
#include "ArrowGameObject.h"
#include "EventHandler.h"
#include "Game.h"

class Game;

using namespace std;
using Point2D = Vector2D;
const int BOW_SPEED = 20;					//Velocidad de movimiento del bow
const uint GAP = 31;						//Desfase gráfico que hay entre el arco cargado y el descargado

//La clase Bow es hija de ArrowGameObject y también de EventHandler
class Bow : public ArrowGameObject,public EventHandler{
private:
	bool charged = true;			//Variable que determina si el bow está cargado
public:
	Bow() {};
	Bow(Point2D _pos, Vector2D _dir, int _h, int _w, int _angle, int _scale, Texture* _texture, Game* _game, int _id);
	virtual void update();
	virtual void handleEvent(const SDL_Event event);
	void changeTexture();
};