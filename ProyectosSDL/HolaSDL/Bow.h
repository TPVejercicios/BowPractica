#pragma once

#include "Texture.h"
#include "Vector2D.h"

using namespace std;
using Point2D = Vector2D;
const int VELOCITYB = 1;

class Bow {
private:
	int xC = 100, xD = 40, y = 100, dist = 31;	//Tamaño
	Vector2D dir;	//Direccion del arco
	Point2D pos;	//Esquina superior izquierda
	Texture* textureC = nullptr;
	Texture* textureD = nullptr;
	//Puntero a la flecha cargada
	//Puntero al juego para informar sobre flechas lanzadas
	//Game* game = nullptr;
	bool cargado = true;

public:
	Bow(Texture* t1, Texture* t2);
	~Bow() {};
	void update();
	void handleEvents(const SDL_Event event);		//Contrala el input
	void render(SDL_Renderer* renderer) const;


	//Auxiliar boorrable
	int devuelvePos() { return pos.getY(); };
};