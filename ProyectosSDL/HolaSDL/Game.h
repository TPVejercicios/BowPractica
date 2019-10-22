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
// EN la practica dice que hay que poner veocidad de globos constante


class Game {
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool exit = false;
	vector<Texture*> textures;
	vector<image> images;
	int points = 0;
	int numArrow = NUM_ARROWS;
	//Bow* bow = new Bow();
	//vector de globos
	//objecto flecha
	void createBallons();			//Genera globos en funcion del frame rate
	//Faltan los punteros a todos los objetos del juego , bow,vector globos...
	//vector de flechas y vector de globos
public:
	Game() {
		SDL_Init(SDL_INIT_EVERYTHING);
		window = SDL_CreateWindow("First test with SDL", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (window == nullptr || renderer == nullptr)
			cout << "Error cargando SDL" << endl;
		else
		{
			LoadPaths();
			//cargar texturas
			for (int i = 0; i < NUM_TEXTURES; i++) {
				Texture* aux = new Texture(renderer, images[i].path, images[i].rows, images[i].colls);
				textures.push_back(aux);
			}
			//bow
			//bow = new Bow(textures.at(1));
			//vector de ballons
		}
	}

	~Game() { DeleteGame(); }

	void LoadPaths();
	void DeleteGame();
	void run();
	void render() const;
	void handleEvents();
	void update();
	void throwArrow();		//Lanza nueva flecha

	//un m´etodo para determinar si
	//dado un globo alguna punta de flecha choca con ´el(que invocar´a el propio globo al actualizarse), y
	//finalmente,
};




