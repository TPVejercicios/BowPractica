#pragma once
#include "Texture.h"
#include <vector>
#include <string>
#include <iostream>
#include "Bow.h"

using namespace std;

const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;
const uint NUM_TEXTURES = 7;
const uint NUM_ARROWS = 10;
const uint FRAME_RATE = 30;
const uint BOW_MOVEMENT = 30;
const uint ARROW_VELOCITY = 30;
const string PATHS[] = { "..\\images\\bg1.png","..\\images\\Bow1.png","..\\images\\Bow2.png","..\\images\\Arrow1.png","..\\images\\Arrow2.png","..\\images\\balloons.png","..\\images\\digits1.png" };

struct image
{
	string path;
	uint colls, rows;
};


class Game {
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool exit = false;
	vector<Texture*> textures;
	vector<image> images;
	int points = 0;
	int numArrow = NUM_ARROWS;
	Bow* bow = nullptr;				//Puntero a globo
	void createBallons();			//Genera globos en funcion del frame rate
public:
	Game();
	~Game() { DeleteGame(); }

	void LoadPaths();
	void DeleteGame();
	void run();
	void render() const;
	SDL_Event handleEvents();
	void update(SDL_Event);
	void throwArrow();		//Lanza nueva flecha

	//un m´etodo para determinar si
	//dado un globo alguna punta de flecha choca con ´el(que invocar´a el propio globo al actualizarse), y
	//finalmente,
};



