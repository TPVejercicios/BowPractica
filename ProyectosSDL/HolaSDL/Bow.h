#pragma once

#include "Texture.h"
#include "Vector2D.h"

using namespace std;
using Point2D = Vector2D;
const int VELOCITYB = 1;

class Bow {
private:
	int x = 100, y = 100;	//Tamaño
	Vector2D dir;	//Direccion del arco
	Point2D pos;	//Esquina superior izquierda
	Texture* texture = nullptr;
	//Puntero a la flecha cargada
	//Puntero al juego para informar sobre flechas lanzadas
	//Game* game = nullptr;
	bool charged = true;

public:
	Bow(Texture* t);
	~Bow() {};
	void update();
	void handleEvents(const SDL_Event event);		//Contrala el input
	void render(SDL_Renderer* renderer) const;
};