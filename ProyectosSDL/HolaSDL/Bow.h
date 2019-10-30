#pragma once
#include "Texture.h"
#include "Vector2D.h"
#include "Arrow.h"

class Game;

using namespace std;
using Point2D = Vector2D;
const int VELOCITYB = 20;

class Bow {
private:
	int xC = 100, xD = 40, y = 100, dist = 31;	//Tamaño
	int tirosRestantes;
	Vector2D dir;					//Direccion del arco
	Point2D pos;					//Esquina superior izquierda
	Texture* textureC = nullptr;
	Texture* textureD = nullptr;
	SDL_Rect* bodyBow = nullptr;
	bool cargado = true;
	Arrow* arrow = nullptr;

public:
	Bow(Texture* t1, Texture* t2, Texture* t3, Texture* t4, int r);
	~Bow();
	void update();
	void handleEvents(const SDL_Event event);		
	void render() const;
	int devuelvePosY() { return pos.getY(); };		//Devuelve la posición en Y del bow
	bool getDisparadaBow() { return arrow->getDisparada(); };
	SDL_Rect* returnArrowHeadBow() { return arrow->returnArrowHead(); };
};