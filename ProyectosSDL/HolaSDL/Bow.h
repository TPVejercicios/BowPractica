#pragma once

#include "Texture.h"
//#include "Vector2D.h"
#include "Game.h"

const int VELOCITY = 5;
using namespace std;
//using Point2D = Vector2D;

class Bow {
private:
	uint w = 0;
	uint h = 0;
	int x = 100, y = 100;
	//Vector2D dir;	//direccion del arco
	//Point2D pos;	//Esquina superior izquierda
	Texture* texture = nullptr;
	//Puntero a la flecha cargada
	//Puntero al juego para informar sobre flechas lanzadas
	//Game* game = nullptr;
	bool charged = true;

public:
	Bow() {};
	Bow(Texture* t) { texture = t; };
	~Bow() {};
	void update();
	void handleEvents();		//Contrala el input
	void render() const;
};