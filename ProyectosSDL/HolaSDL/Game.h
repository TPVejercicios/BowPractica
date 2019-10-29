#pragma once
#include "Texture.h"
#include <vector>
#include <string>
#include <iostream>
#include "Bow.h"
#include "Arrow.h"
#include "Ballon.h"

using namespace std;
using Goblos = vector<Ballon*>;
const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;
const uint NUM_TEXTURES = 7;
const uint FRAME_RATE = 30;
const uint FRAME_BALLON = 1000;
const uint NUM_ARROWS = 5;
const string BASE_NAME = "..\\images\\";
const string PATHS[] = { "..\\images\\bg1.png","..\\images\\Bow1.png","..\\images\\Bow2.png","..\\images\\Arrow1.png","..\\images\\Arrow2.png","..\\images\\balloons.png","..\\images\\digits1.png" };

struct image
{
	string path;
	uint colls, rows;
};


class Game {
private:
	int points = 0;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool exit = false;
	vector<Texture*> textures;
	vector<Texture*> texBallons;
	vector<image> images;
	Texture* background = nullptr;
	Bow* bow = nullptr;				//Puntero a globo
	Arrow* arrow = nullptr;			//Puntero a flecha
	Goblos globos;					//Vector de punteros de globos
	void createBallons();			//Genera globos en funcion del frame rate
public:
	Game();
	~Game() { DeleteGame(); }
	void LoadPaths();
	void DeleteGame();
	void run();
	void render() const;
	void handleEvents();
	void update();			//Manda actualizarse a cada objeto del juego
	void checkCrushBallon();
	void showPoints() { system("cls"); cout << "PUNTOS: " << points << endl; };

	//un método para determinar si
	//dado un globo alguna punta de flecha choca con ´el(que invocar´a el propio globo al actualizarse), y
	//finalmente,
};



