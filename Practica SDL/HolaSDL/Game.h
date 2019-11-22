#pragma once
#include <vector>
#include <string>
#include "SDL.h"
#include "SDL_image.h"
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

using namespace std;
using uint = unsigned int;

const uint WIN_WIDTH = 800;							//Anchura del juego
const uint WIN_HEIGHT = 600;						//Altura del juego
const uint NUM_TEXTURES = 15;						//Num de texturas
const uint FRAME_RATE = 30;							//Frames que determinan un ciclo de vida del juego
const uint FRAME_BALLON = 500;						//Frames que determinan la generación de globos
const int SCALE_DIV = 4;							//Escala para dividir sprites 

//Constantes para la creación de bow
const uint START_BOW_POS_X = 0;
const uint BOW_POS_Y = 0;
const uint BOW_H = 100;
const uint BOW_W = 100;
const uint BOW_SCALE = 4;
const int BOW_ID = 1;

//Constantes para la creación de arrow
const uint ARROW_H = 20;
const uint ARROW_W = 100;
const uint NUM_ARROWS = 10;
const int ARROW_ID = 2;

//Constantes para la creación de una butterfly
const uint BUTTERFLY_H = 50;
const uint BUTTERFLY_W = 25;
const int BUTTERFLY_ID = 7;
const uint BUTT_MIN_X = 300;
const uint BUTT_MAX_X = 750;
const uint BUTT_MAX_Y = 550;


//Constantes para los puntos
const int POINTS_TO_ADD = 10;
//Constantes para la creación de ballon
const uint BALLON_H = 100;
const uint BALLON_W = 100;
const uint BALLON_MIN_POS_X = 300;
const uint BALLON_MAX_POS_X = 800 - BALLON_W;
const uint BALLON_MIN_POS_Y = 700;
const uint BALLON_MAX_SPEED = 18;
const uint BALLON_MIN_SPEED = 5;
const int BALLON_ID = 3;


struct image	//Estructura que ayuda a organizar la carga de texturas
{
	string filename;
	uint colls, rows;
};

struct level {
	int butterflyNum;
	int arrows;
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

class Game
{
private:
	int	points = 0;							//Puntos conseguidos
	int remainingShots = NUM_ARROWS;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool exit = false;						//Bool que determina el bucle del juego
	Texture* textures[NUM_TEXTURES];		//Array de texturas
	Background* background = nullptr;				//Puntero al background
	vector<GameObject*> gameObjects;		//Vector con TODOS los objetos del juego
	vector<EventHandler*> eventObjects;		//Vector con los objetos que tienen que comprobar eventos
	vector<Arrow*> arrows;
	vector<GameObject*> objectsToErase;
	ScoreBoard* SCB = nullptr;

	void loadTextures();
	void render();
	void handleEvents();
	void update();
	void mostrarGameObjects();
	void createBow();
	void deleteObjects();
	void createBallons();
	void createScoreBoard();
	void checkCollisions();
	void createButterfly();
public:
	Game();
	~Game();
	void run();
	void createArrow(Vector2D _pos);
	int getRemainingShots() { return remainingShots; };
	int getPoints() { return points; };
	Texture* getTextureBow(bool charged) { return charged ? textures[BOW_1] : textures[BOW_2]; };
	void killObject(ArrowGameObject* _object) {objectsToErase.push_back(_object);};
	void gime100Arrows() { remainingShots += 100; };

	//void killArrow(Arrow* _arrow) {objectsToErase.push_back(_arrow);};
};

