#include "Game.h"
#include "ScoreBoard.h"

//Constructor de scoreBoard
ScoreBoard::ScoreBoard(Texture* _score, Texture* _arrow,Game* _game) {
	game = _game;
	scoreTexture = _score;
	arrowTexture = _arrow;
	updateArrowHUD();
	render();
}

//Destructora de scoreBoard
ScoreBoard::~ScoreBoard() {
	scoreTexture = nullptr;
	arrowTexture = nullptr;
}


//Renderiza puntos y flechas restantes
void ScoreBoard::render() const{
	renderPoint();
	renderArrowHUD();
}

void ScoreBoard::renderPoint()const {
	for (int i = 0; i < marcador.size(); i++) {
		scoreTexture->renderFrame({ marcador.at(i).x, 10, DIGIT_RECT_W, DIGIT_RECT_H },0, marcador.at(i).value, SDL_FLIP_NONE);
	}
}

//Esto está mal...
void ScoreBoard::updatePoints(int _points) {
	marcador.clear();
	currentPoints = _points;
	int x = START_SCORE_POS;
	int aux = (char)to_string(currentPoints).size();
	score currScore;
	for (int i = 0; i < aux; i++) {
		currScore.value = (int)to_string(currentPoints).at(i) - 48;
		currScore.x = x;
		x -= DIGIT_RECT_W;
		marcador.push_back(currScore);
	}
}

void ScoreBoard::renderArrowHUD() const {
	for (int i = 0; i < arrowLeft; i++) {
		arrowTexture->render({ arrowsPosX.at(i),10,ARROW_RECT_W,ARROW_RECT_H }, SDL_FLIP_NONE);
	}
}
//Guarda en un vector las posiciones de las arrows 
void ScoreBoard::updateArrowHUD() {
	arrowLeft = game->getRemainingShots();
	int x = START_ARROW_POS;
	for (int i = 0; i < arrowLeft; i++) {
		arrowsPosX.push_back(x);
		x += ARROW_GAP;
	}
}

