#pragma once
#include "Texture.h"
#include <vector>
#include <string>
#include <iostream>
#include "GameObject.h"

using namespace std;
using Ballons = vector<Ballon*>;
const uint WIN_WIDTH = 800;							//Anchura del juego
const uint WIN_HEIGHT = 600;						//Altura del juego
const uint NUM_TEXTURES = 7;						//Num de texturas
const uint FRAME_RATE = 30;							//Frames que determinan un ciclo de vida del juego
const uint FRAME_BALLON = 500;						//Frames que determinan la generación de globos
const string PATHS[] = { "..\\images\\bg1.png","..\\images\\Bow1.png","..\\images\\Bow2.png","..\\images\\Arrow1.png","..\\images\\Arrow2.png","..\\images\\balloons.png","..\\images\\digits1.png" };
const int SCALE_DIV = 4;							//Escala para dividir sprites 

struct image										//Estructura que ayuda a organizar la carga de texturas
{
	string path;
	uint colls, rows;
};


class Game {
private:
	int					points			= 0;		//Puntos conseguidos
	SDL_Window*			window			= nullptr;
	SDL_Renderer*		renderer		= nullptr;
	bool				exit			= false;	//Bool que determina el bucle del juego
	vector<Texture*>	textures;					//Vector de texturas
	vector<image>		images;						//vector con información para cargar las texturas
	Bow*				bow				= nullptr;	//Puntero a bow
	Ballons				ballons;					//Vector de punteros a ballons
	SDL_Rect*			pointsPointer	= nullptr;	//Rect para renderizar los puntos 
	SDL_Rect*			arrowHUD		= nullptr;	//Rect para renderizar las arrows en el HUB
	SDL_Rect*			backgroundPos	= nullptr;	//Rect para renderizar el fondo
	ScoreBoard*			scoreBoard		= nullptr;	//Puntero a la clase ScoreBoard

	void createBallons();		
	void LoadPaths();
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



