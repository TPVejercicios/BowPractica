#pragma once


const int SLIP_ARROW = 8;
const int SLIP_POINTS = 10;
const int SCALE_POINTS = 50;
const int START_ARROW_POS = 200;
const int ARROW_GAP = 10;
const int POINTS_GAP = 35;

class Game;
class ArrowGameObject;
class Vector2D;
class Texture;
using Point2D = Vector2D;

//Scorebord hereda de GameObject
class ScoreBoard : public GameObject {
private:
	int currentPoints = 0, arrowLeft = 0;
	Texture*	arrowTexture	= nullptr;
	Texture*	scoreTexture	= nullptr;
	SDL_Rect*	pointerRect		= nullptr;
	SDL_Rect*	arrowRect		= nullptr;
	void updatePoints();
	void updateArrowHUD();

public:
	ScoreBoard(Texture* score, Texture* arrow);
	~ScoreBoard();
	void render(int points,int arrows);

};

