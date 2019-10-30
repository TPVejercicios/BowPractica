#pragma once
#include "Texture.h"
#include "Vector2D.h"
class Bow;
class Game;

using Point2D = Vector2D;

const int VELOCITYA = 30;
const int VELOCITYC = 20;

class Arrow
{
private:
	Point2D pos;				//Posici�n
	int x = 100, y = 20;		//Ancho y alto
	int disT = 44, disD = 37;	//Valores de centrado de la flecha con respecto al arco
	int hudX = 200, hudY = 0, hudW = y/2, hudH = x/2;	//Posiciones de las flechas de la rec�mara
	int gap = 80;				//Distancia para coger el rect de la cabeza de la flecha
	int restantes;				//N�mero de flechas restantes
	Vector2D dir;				//Vector direcci�n del disparo
	Texture* texture = nullptr;
	Texture* texture2 = nullptr;
	SDL_Rect* arrowFull = nullptr;
	SDL_Rect* arrowHead = nullptr;
	SDL_Rect* arrowHUD = nullptr;
	Bow* bow = nullptr;
	bool disparada = false, finDisparo = false;

public:
	Arrow(Texture* t, Texture* t2, int r,Bow* b);
	~Arrow();
	void update();
	void render() const;
	void Arrow::renderHUD() const;
	void recargar(const int posYArco);
	void setDisparada(bool estado) { disparada = estado; };
	bool getDisparada() { return disparada; };
	bool devuelveFin() { return finDisparo; };
	SDL_Rect* returnArrowHead() { return arrowHead; };
	void setDirection(int x, int y);
};