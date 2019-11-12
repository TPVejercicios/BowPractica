
#include "ScoreBoard.h"


using namespace std;

//Constructor de scoreBoard
ScoreBoard::ScoreBoard(Texture* score, Texture* arrow,Game* game) 
	:ArrowGameObject(game)
{
	scoreTexture = score;
	arrowTexture = arrow;
	
	arrowRect = new SDL_Rect();
	arrowRect->h = arrowTexture->getH() / SLIP_ARROW;
	arrowRect->w = arrowTexture->getW() / SLIP_ARROW;
	arrowRect->x = START_ARROW_POS;
	arrowRect->y = 0;

	pointerRect = new SDL_Rect();
	pointerRect->h = pointerRect->w = SCALE_POINTS;
	pointerRect->x = SCALE_POINTS; pointerRect->y = 0;

}

//Destructora de scoreBoard
ScoreBoard::~ScoreBoard() {

	try {
		scoreTexture = nullptr;
		arrowTexture = nullptr;
		delete arrowRect;
		delete pointerRect;
		cout << "Se ha eliminado el scoreBoard" << endl;
	}
	catch (exception e) {
		cout << "Error deleting scoreBoard " << e.what() << endl;
	}

}


//Renderiza puntos y flechas restantes
void ScoreBoard::ActualizaHUD(int arrows) {
	arrowLeft = arrows;
	updatePoints();
	updateArrowHUD();
}

//Actualiza los valores de puntos 
void ScoreBoard::updatePoints() {
	string pointsString = to_string(game->pointsGame());
	int nums = pointsString.size();
	//48 es el valor a restar para convertir un char en int (Codigo ASCII)
	int iter = 0;
	int aux = pointerRect->x;
	for (int i = 0; i < nums; i++) {
		iter = (int)(pointsString[i]) - 48;
		scoreTexture->renderFrame(*pointerRect, 0, iter, 0, SDL_FLIP_NONE);
		pointerRect->x += POINTS_GAP;
	}
	pointerRect->x = aux;
}

//Actualiza la cantidad de flechas restantes
void ScoreBoard::updateArrowHUD() {
	int distance = arrowRect->x;

	for (int i = 0; i < arrowLeft; i++) {
		arrowTexture->render(*arrowRect, SDL_FLIP_NONE);
		arrowRect->x += ARROW_GAP;
	}
	arrowRect->x = distance;
}
