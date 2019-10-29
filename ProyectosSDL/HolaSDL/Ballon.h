#pragma once
#include "Texture.h"
#include "Vector2D.h"
class Game;

using namespace std;
using Point2D = Vector2D;
const int MAX_BALLON_SPEED = 5;

enum punctured
{
	PUNCTURED = 0,
	SWOLLEN = 1
};

class Ballon{
private:
	punctured status = SWOLLEN;
	Point2D pos;
	Vector2D vel;
	uint timePunctured;
	int numTexture, numBallon, collFrame = 0, gap = 10, bodySize = 80;
	Texture* texture = nullptr;
	Game* game = nullptr;
	SDL_Rect* ballonBody = nullptr;
public:
	Ballon() {};
	Ballon(Texture* t, Game* g);
	~Ballon();
	bool update();
	void render(SDL_Renderer* renderer) const;
	//cambia el estado del globo para empezar la animación de rotura
	void ballonPunctured() { status = PUNCTURED; };	
	//Devuelve el Rect del ballon
	SDL_Rect* returnBallonBody() { return ballonBody; };
	//Devuelve true si el globo está inflado 
	bool returnState() { return status == SWOLLEN ? true : false; };
};

