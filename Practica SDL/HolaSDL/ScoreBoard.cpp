#include "Game.h"
#include "ScoreBoard.h"

//Constructor de scoreBoard
ScoreBoard::ScoreBoard(Texture* _score, Texture* _arrow, int _points, int _arrows, Game* _game) {
	scoreTexture = _score;
	arrowTexture = _arrow;
	arrowsToRender = _arrows;
	game = _game;
	cout << "Creado SCB" << endl;
	updatePoints(_points);
	render();
}

//Destructora de scoreBoard
ScoreBoard::~ScoreBoard(){
	scoreTexture = nullptr;
	arrowTexture = nullptr;

}

void ScoreBoard::renderPoint()const {
	for(int i = 0; i < marcador.size(); i++) {
		scoreTexture->renderFrame({ marcador.at(i).x, 10, DIGIT_RECT_W, DIGIT_RECT_H }, 0, marcador.at(i).value, SDL_FLIP_NONE);
	}
}

//Renderiza las flechas //POS_CAMINO_X + CAMINO_SIZE_X * i
void ScoreBoard::renderArrowHUD() const {
	int arrowsToRender = game->getRemainingShots();
	for (int i = 0; i < arrowsToRender; ++i) {
		arrowTexture->render({(START_ARROW_POS + ARROW_GAP * i) + ARROW_GAP,10,ARROW_RECT_W,ARROW_RECT_H }, SDL_FLIP_NONE);
	}
}

//Renderiza puntos y flechas restantes
void ScoreBoard::render() const{
	renderPoint();
	renderArrowHUD();
}


void ScoreBoard::updatePoints(int _points) {
	marcador.clear();
	currentPoints = _points;
	int x = START_SCORE_POS;
	int aux = (char)to_string(currentPoints).size();
	score currScore;
	for (int i = 0; i < aux; i++) {
		currScore.value = (int)to_string(currentPoints).at(i) - 48;
		currScore.x = x;
		x += DIGIT_RECT_W;
		marcador.push_back(currScore);
	}
}
