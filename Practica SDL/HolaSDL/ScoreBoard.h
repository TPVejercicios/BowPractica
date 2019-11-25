#pragma once
#include "GameObject.h"

class Game;

const int SLIP_ARROW = 8;
const int SLIP_POINTS = 10;
const int SCALE_POINTS = 50;
const int START_ARROW_POS = 300;
const int ARROW_GAP = 10;

//Constantes para renderizar arrows
const int ARROW_RECT_W = 10;
const int ARROW_RECT_H = 50;

//Constantes para renderizar los puntos
const int START_SCORE_POS = 150;
const int DIGIT_RECT_H = 50;
const int DIGIT_RECT_W = 35;


struct score
{
	int x;
	int value;
};

class ScoreBoard : public GameObject {
private:
	int currentPoints = 0, arrowsToRender = 0;
	Texture* arrowTexture = nullptr;
	Texture* scoreTexture = nullptr;
	Game* game = nullptr;
	vector<score> marcador;
	void renderPoint() const;
	void renderArrowHUD() const;
public:
	ScoreBoard(Texture* _score, Texture* _arrow, int _points, int _arrows, Game* _game);
	~ScoreBoard();
	virtual void render() const;
	virtual void update() {};
	void updatePoints(int _points);
	void updateArrows(int _numArrows) { arrowsToRender = _numArrows; };
	void arrowsCheat(int _nums) { arrowsToRender += _nums; cout << "Se han cheteado " << _nums << " flechas." << endl; };
};
