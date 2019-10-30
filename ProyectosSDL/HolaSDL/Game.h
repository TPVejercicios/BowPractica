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
const string PATHS[] = { "..\\images\\bg1.png","..\\images\\Bow1.png","..\\images\\Bow2.png","..\\images\\Arrow1.png","..\\images\\Arrow2.png","..\\images\\balloons.png","..\\images\\digits1.png" };
const int POINTS_SCALE = 50;

struct image
{
	string path;
	uint colls, rows;
};


class Game {
private:
	int points = 0, first = 0, second = 0, third = 0;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool exit = false;
	vector<Texture*> textures;
	vector<image> images;
	Bow* bow = nullptr;				//Puntero a globo
	//Arrow* arrow = nullptr;			//Puntero a flecha
	Goblos globos;					//Vector de punteros a globos
	SDL_Rect* firstPointer = nullptr;
	SDL_Rect* secondPointer = nullptr;
	SDL_Rect* thirdPointer = nullptr;

	void createBallons();			
public:
	Game();
	~Game();
	void LoadPaths();
	void run();
	void render() const;
	void handleEvents();
	void update();					
	void checkCrushBallon();		
	void updatePoints(); 
	void renderPoints() const;
};



