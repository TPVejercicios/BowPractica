#pragma once
#include "ArrowGameObject.h"
class Game;

const int SLIP_ARROW = 8;
const int SLIP_POINTS = 10;
const int SCALE_POINTS = 50;
const int START_ARROW_POS = 200;
const int ARROW_GAP = 10;
const int POINTS_GAP = 35;


using Point2D = Vector2D;

//Scorebord hereda de GameObject
class ScoreBoard : public ArrowGameObject {
private:
	int currentPoints = 0, arrowLeft = 0;
	Texture*	arrowTexture	= nullptr;
	Texture*	scoreTexture	= nullptr;
	SDL_Rect*	pointerRect		= nullptr;
	SDL_Rect*	arrowRect		= nullptr;
	void updatePoints();
	void updateArrowHUD();
	void ActualizaHUD(int arrows);
public:
	ScoreBoard(Texture* score, Texture* arrow,Game* game);
	~ScoreBoard();
	virtual void render() const {};
	virtual void update() {};
	
};

