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
	int numTexture;
	int numBallon;
	int collFrame = 0;
	Texture* texture = nullptr;
	Game* game = nullptr;
	SDL_Rect* ballonBody = nullptr;
public:
	Ballon() {};
	Ballon(Texture* t, Game* g);
	~Ballon();
	bool update();
	void render(SDL_Renderer* renderer) const;
	void ballonPunctured(uint time);
	SDL_Rect* returnBallonBody() { return ballonBody; };
	bool returnState() { return status == SWOLLEN ? true : false; };
};

