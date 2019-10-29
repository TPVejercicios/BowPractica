#pragma once
#include "Texture.h"
#include "Vector2D.h"
class Game;

using Point2D = Vector2D;

const int VELOCITYA = 30;
const int VELOCITYC = 20;

class Arrow
{
private:
	Point2D pos;				//Posición
	int x = 100, y = 20;		//Ancho y alto
	int disT = 44, disD = 37;	//Valores de centrado de la flecha con respecto al arco
	int hudX = 200, hudY = 0, hudW = y/2, hudH = x/2;	//Posiciones de las flechas de la recámara
	int restantes;				//Número de flechas restantes
	Vector2D dir;				//Vector dirección del disparo
	Texture* texture = nullptr;
	Texture* texture2 = nullptr;
	SDL_Rect* arrowHead = nullptr;
	Game* game = nullptr;
	bool disparada = false, finDisparo = false;

public:
	Arrow(Texture* t, Texture* t2, int r);
	~Arrow() {};
	void update();
	void handleEvents(const SDL_Event event, const int posYArco);		//Contrala el input
	void render(SDL_Renderer* renderer) const;
	void Arrow::renderHUD(SDL_Renderer* renderer) const;
	void recargar(const int posYArco);
	void setDisparada(bool estado) { disparada = estado; };
	bool getDisparada() { return disparada; };
	bool devuelveFin() { return finDisparo; };
	SDL_Rect* returnArrowHead() { return arrowHead; };
};