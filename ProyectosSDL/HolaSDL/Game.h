#pragma once
#include "Texture.h"
#include <vector>
#include <string>
#include <iostream>
#include "GameObject.h"
#include "Vector2D.h"
using Point2D = Vector2D;

using namespace std;
using Ballons = vector<Ballon*>;
const uint WIN_WIDTH = 800;							//Anchura del juego
const uint WIN_HEIGHT = 600;						//Altura del juego
const uint NUM_TEXTURES = 15;						//Num de texturas
const uint FRAME_RATE = 30;							//Frames que determinan un ciclo de vida del juego
const uint FRAME_BALLON = 500;						//Frames que determinan la generación de globos
const int SCALE_DIV = 4;							//Escala para dividir sprites 

//Array con las texturas y su número de columnas y filas para facilitar la carga
const image PATHS[NUM_TEXTURES] = {{"..\\images\\Arrow1.png", 1, 1}, {"..\\images\\Arrow2.png", 1, 1}, {"..\\images\\Background01.png", 1, 1}, {"..\\images\\Background02.png", 1, 1},
{"..\\images\\Background03.png", 1, 1}, {"..\\images\\Background04.png", 1, 1}, {"..\\images\\Background05.png", 1, 1}, {"..\\images\\Background06.png", 1, 1}, {"..\\images\\Ballons.png", 6, 7}, 
{"..\\images\\Bow1.png", 1, 1}, {"..\\images\\Bow2.png", 1, 1}, {"..\\images\\Bubble.png", 1, 1}, {"..\\images\\Butterfly.png", 10, 4}, {"..\\images\\Digits.png", 10, 1}, {"..\\images\\Rewards.png", 8, 10}};

struct image										//Estructura que ayuda a organizar la carga de texturas
{
	string filename;
	uint colls, rows;
};


class Game {
private:
	int					points			= 0;		//Puntos conseguidos
	SDL_Window*			window			= nullptr;
	SDL_Renderer*		renderer		= nullptr;
	bool				exit			= false;	//Bool que determina el bucle del juego
	vector<Texture*>	textures;					//Vector de texturas
	SDL_Rect*			pointsPointer	= nullptr;	//Rect para renderizar los puntos 
	SDL_Rect*			arrowHUD		= nullptr;	//Rect para renderizar las arrows en el HUB
	SDL_Rect*			backgroundPos	= nullptr;	//Rect para renderizar el fondo
	vector<GameObject*> gameObjects;				//Vector con TODOS los objetos del juego

	void loadTextures();
	void createBallons();		
	void render();
	void handleEvents();
	void update();
public:

	//exception 
	string				loadingIMG	= "Error loading image ";
	string				deletingOBJ = "Error deleting object";

	Game();
	~Game();
	void run();
	void checkCrushBallon();
};



