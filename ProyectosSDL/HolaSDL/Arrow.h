#pragma once
#include "Texture.h"
#include "Vector2D.h"
using Point2D = Vector2D;

const int VELOCITYA = 1;
const int NUM_ARROWS = 10;

class Arrow
{
private:
	Point2D pos;			//Posición
	int x = 100, y = 20;	//Ancho y alto
	int restantes = NUM_ARROWS;
	Vector2D dir;
	Texture* texture = nullptr;
	bool disparada = false;

public:
	Arrow(Texture* t);
	~Arrow() {};
	void update();
	void handleEvents(const SDL_Event event);		//Contrala el input
	void render(SDL_Renderer* renderer) const;
	void recargar(int);
	void setDisparada(bool estado) { disparada = estado; };
	bool getDisparada() { return disparada; };


	//Auxiliar borrable
	int valorNeed() { return pos.getY(); };
};