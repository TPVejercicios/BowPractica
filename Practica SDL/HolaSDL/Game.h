#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include <time.h>
#include <math.h>
#include <fstream>
#include "Texture.h"
#include "GameObject.h"
#include "EventHandler.h"
#include "Vector2D.h"
#include <list>
#include "Background.h"
#include "Arrow.h"
#include "Ballon.h"
#include "ScoreBoard.h"
#include "Butterfly.h"
#include "Bow.h"
#include "Reward.h"

using namespace std;
using uint = unsigned int;

//Constantes para game
const uint WIN_WIDTH = 800;							//Anchura del juego
const uint WIN_HEIGHT = 600;						//Altura del juego
const uint NUM_TEXTURES = 15;						//Num de texturas
const uint FRAME_RATE = 30;							//Frames que determinan un ciclo de vida del juego
const int SCALE_DIV = 4;							//Escala para dividir sprites 
const int MAX_LEVELS = 5;

//Constantes para la creación de bow
const uint START_BOW_POS_X = 0;
const uint BOW_POS_Y = 0;
const uint BOW_H = 100;
const uint BOW_W = 100;
const uint BOW_SCALE = 1;
const int BOW_ID = 0;

//Constantes para la creación de arrow
const uint ARROW_H = 20;
const uint ARROW_W = 100;
const int ARROW_ID = 1;

//Constantes para la creación de una butterfly
const uint BUTTERFLY_H = 96;
const uint BUTTERFLY_W = 93;
const uint BUTT_MIN_X = 150;
const uint BUTT_MAX_X = 750;
const uint BUTT_MAX_Y = 550;
const int BUTTERFLY_ID = 3;

//Constantes para rewards 
const uint REWARD_H = 30;
const uint REWARD_W = 50;
const uint REWARD_SPEED = 2; //Cambiar a 5 he puesto 2 porque se me escapaban
const int REWARD_ID = 4;
const int MAX_REWARDS = 4;

//Constantes para los puntos
const int POINTS_TO_ADD = 10;
const int BONUS_POINTS = 2;
const int POINTS_TO_SUB = 15;


//Constantes para la creación de ballon
const uint BALLON_H = 100;
const uint BALLON_W = 100;
const uint BALLON_MIN_POS_X = 300;
const uint BALLON_MAX_POS_X = 800 - BALLON_W;
const uint BALLON_MIN_POS_Y = 700;
const uint BALLON_MAX_SPEED = 18;
const uint BALLON_MIN_SPEED = 5;
const int BALLON_ID = 2;

//Estructura que ayuda a organizar la carga de texturas
struct image	
{
	string filename;
	uint colls, rows;
};

//Array con las texturas y su número de columnas y filas para facilitar la carga
const image PATHS[] = { {"..\\images\\Arrow1.png", 1, 1}, {"..\\images\\Arrow2.png", 1, 1}, {"..\\images\\Background01.png", 1, 1}, {"..\\images\\Background02.png", 1, 1},
{"..\\images\\Background03.png", 1, 1}, {"..\\images\\Background04.png", 1, 1}, {"..\\images\\Background05.png", 1, 1}, {"..\\images\\Background06.png", 1, 1}, {"..\\images\\Ballons.png", 6, 7},
{"..\\images\\Bow1.png", 1, 1}, {"..\\images\\Bow2.png", 1, 1}, {"..\\images\\Bubble.png", 1, 1}, {"..\\images\\Butterfly.png", 10, 4}, {"..\\images\\Digits.png", 10, 1}, {"..\\images\\Rewards.png", 8, 10} };

//Indice de texturas
enum indexTexturas
{
	ARROW_1 = 0, ARROW_2 = 1, BG_1 = 2, BG_2 = 3, BG_3 = 4, BG_4 = 5, BG_5 = 6, BG_6 = 7, BALLONS = 8, BOW_1 = 9, BOW_2 = 10, BUBBLE = 11, BUTTERFLY = 12, DIGITS = 13, REWARDS = 14
};

enum indexObjets {
	OBJECT_BOW = 0, OBJECT_ARROW = 1, OBJECT_BALLON = 2, OBJECT_BUTTERFLY = 3, OBJECT_REWARD = 4
};

//Estructura para definir cada nivel
struct level {
	 indexTexturas currTex;
	 int butterflyNum;
	 int arrows;
	 int pointsToReach;
	 uint frame_ballon;
};
//Array constante para determinar los valores de cada nivel
const level LEVELS[] = {
	{BG_1,5,10,50,500},		//nivel 1
	{BG_2,10,12,250,450},	//nivel 2
	{BG_3,12,15,550,400},	//nivel 3
	{BG_4,15,18,800,350},	//nivel 4
	{BG_5,16,20,1000,250},	//nivel 5
	{BG_6,20,25,1250,175}	//nivel 6
};

class Game
{
private:
	int	currPoints = 0;						//Puntos conseguidos
	int currArrows = 0;						//El número de flechas restantes
	int currLevel = 0;						//El acutal nivel
	int currButterflies = 0;				//El actual número de mariposas restantes en la escena
	int ballonScale = 1;					//Para implementa un reward que aumenta su tamaño 
	bool bowCharged = true;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool exit = false;						//Bool que determina el bucle del juego
	Texture* textures[NUM_TEXTURES];		//Array de texturas
	Background* background = nullptr;		//Puntero al background
	list<GameObject*> gameObjects;			//Vector con TODOS los objetos del juego
	list<GameObject*> eventObjects;			//Vector con los objetos que tienen que comprobar eventos
	list<Arrow*> arrows;					//Lista de las flechas del juego
	list<GameObject*> objectsToErase;		//Lista de los objetos a borrar
	ScoreBoard* SCB = nullptr;				//Puntero a la scoreBoard
	
	//Métodos creadores
	void loadTextures();
	void createBow();
	void createBallons();
	void createScoreBoard();
	void createButterfly();

	//Métodos virtuales
	void render();
	void handleEvents();
	void update();
	//Métodos destructores
	void deleteAllbutterflies();
	void deleteAllRewards();
	void deleteAllBallons();
	void deleteAllArrows();
	void deleteObjects();
	//Métodos gestionadores
	void loadLevel();
	void nextLevel();
	//Métodos checkers
	void mostrarGameObjects();
	void checkCollisions();
	bool endGame();
public:
	Game(int partida);
	~Game();
	void run();
	void createArrow(Vector2D _pos);	
	int getRemainingShots() { return currArrows; };
	Texture* getTextureBow(bool charged);
	void killObject(GameObject* _object) {objectsToErase.push_back(_object);};
	void gime100Arrows() { currArrows += 100; SCB->arrowsCheat(100); };
	void arrowStacks(int _stacks);
	void info();
	void addArrows(int _arrowsToAdd) { currArrows += _arrowsToAdd; };
	void addButterflies(int _butterfliesToAdd);
	void setBallonScale(int _newScale) { ballonScale = _newScale; };
	void createReward(Point2D _pos);
	int getNumPoints() { return currPoints; };
	void saveGame(int partida);
};

