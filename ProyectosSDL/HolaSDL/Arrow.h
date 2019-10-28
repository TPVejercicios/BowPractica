#pragma once
#include "Texture.h"
#include "Vector2D.h"
using Point2D = Vector2D;
const int VELOCITYA = 20;

class Arrow
{
private:
	Point2D pos;		//Posición
	int x = 100, y = 100;	//Ancho y alto
	Vector2D dir;
	Texture* texture = nullptr;
	bool disparada = false;

public:
	Arrow() {};
	Arrow(Texture* t);
	~Arrow() {};
	void update();
	void handleEvents();		//Contrala el input
	void render() const;
	void recargar(int);
	void setDisparada(bool estado) { disparada = estado; };
	bool getDisparada() { return disparada; };
};