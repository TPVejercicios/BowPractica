#pragma once

#include "Texture.h"
#include "Vector2D.h"
#include "Arrow.h"

using namespace std;
using Point2D = Vector2D;
const int VELOCITYB = 5;

class Bow {
private:
	int x = 100, y = 100;	//Tamaño
	Vector2D dir;	//Direccion del arco
	Point2D pos;	//Esquina superior izquierda
	Texture* texture = nullptr;
	Arrow*  arrow = nullptr;
	//Puntero a la flecha cargada
	//Puntero al juego para informar sobre flechas lanzadas
	//Game* game = nullptr;
	bool charged = true;

public:
	Bow(Texture* t);
	~Bow() {};
	void update(SDL_Event);
	void handleEvents();		//Contrala el input
	void render() const;
};