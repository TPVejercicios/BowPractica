#pragma once
#include <vector>
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "Texture.h"
#include <iostream>

#include "Bow.h"
#include "Background.h"
#include "Ballon.h"
#include "ScoreBoard.h"
#include "GameObject.h"




using namespace std;
using uint = unsigned int;

const uint WIN_WIDTH = 800;							//Anchura del juego
const uint WIN_HEIGHT = 600;						//Altura del juego
const uint NUM_TEXTURES = 15;						//Num de texturas
const uint FRAME_RATE = 30;							//Frames que determinan un ciclo de vida del juego
const uint FRAME_BALLON = 500;						//Frames que determinan la generación de globos
const int SCALE_DIV = 4;							//Escala para dividir sprites 

struct image										//Estructura que ayuda a organizar la carga de texturas
{
	string filename;
	uint colls, rows;
};

//Array con las texturas y su número de columnas y filas para facilitar la carga
const image PATHS[] = { {"..\\images\\Arrow1.png", 1, 1}, {"..\\images\\Arrow2.png", 1, 1}, {"..\\images\\Background01.png", 1, 1}, {"..\\images\\Background02.png", 1, 1},
{"..\\images\\Background03.png", 1, 1}, {"..\\images\\Background04.png", 1, 1}, {"..\\images\\Background05.png", 1, 1}, {"..\\images\\Background06.png", 1, 1}, {"..\\images\\Ballons.png", 6, 7}, 
{"..\\images\\Bow1.png", 1, 1}, {"..\\images\\Bow2.png", 1, 1}, {"..\\images\\Bubble.png", 1, 1}, {"..\\images\\Butterfly.png", 10, 4}, {"..\\images\\Digits.png", 10, 1}, {"..\\images\\Rewards.png", 8, 10}};

class Game {
private:
	int	points = 0;							//Puntos conseguidos
	int arrowsRemain = 0;
	SDL_Window*	window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool exit = false;							//Bool que determina el bucle del juego
	vector<Texture*> textures;					//Vector de texturas
	vector<ArrowGameObject*> gameObjects;		//Vector polimórfico con TODOS los objetos del juego
	bool shooted = false;


	void loadTextures();
	void createBallons();		
	void render();
	void handleEvents();
	void update();

public:

	//exception 
	string loadingIMG = "Error loading image ";
	string deletingOBJ = "Error deleting object";

	Game();
	~Game();
	int pointsGame() { return points; };
	void addArrowsCounts(int arrows) { arrowsRemain = arrows; };
	void bowShoted() { shooted = true; };
	void checkCrushBallon(SDL_Rect* ballonColl);
	void run();
};



