#include "Game.h"
#include <iostream>
#include "Bow.h"
#include "Background.h"

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Practica2", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr)
		cout << "Error cargando SDL" << endl;
	else
	{
		//Carga texturas
		loadTextures();
		//Crea el background y el bow
		background = new Background(WIN_HEIGHT, WIN_WIDTH, textures[BG_4]);
		createBow();
	}
}

//Destructora, llama a todos los destructores de la clase game
Game::~Game() {

}

//Bucle principal del juego
void Game::run() {
	uint32_t startTime, frameTime, createBallon, ballonCreated;
	startTime = ballonCreated = SDL_GetTicks();
	while (!exit) {
		handleEvents();
		createBallon = SDL_GetTicks() - ballonCreated;
		frameTime = SDL_GetTicks() - startTime;
		if (frameTime >= FRAME_RATE) {
			update();
			render();	
			mostrarGameObjects(); //Auxiliar para debug
			startTime = SDL_GetTicks();
		}
		if (createBallon >= FRAME_BALLON) {
			//createBallons();
			ballonCreated = SDL_GetTicks();
		}
	}
	cout << "Fin del juego" << endl;
}

void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type != SDL_QUIT) {
			for (int i = 0; i < eventObjects.size(); i++) {
				eventObjects.at(i)->handleEvents(event);
			}
		}
		else exit = true;
	}
}

//Dibuja cada objeto en el SDL_Renderer
void Game::render() {
	SDL_RenderClear(renderer);
	background->render();
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects.at(i)->render();
	}
	SDL_RenderPresent(renderer);
}

//Hace las llamadas a los updates de todos los objetos del juego
void Game::update() {
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects.at(i)->update();
	}
}

//Carga las texturas en un vector (couts for debug)
void Game::loadTextures() {
	try {
		for (int i = 0; i < NUM_TEXTURES; i++) {
			textures[i] = new Texture(renderer, PATHS[i].filename, PATHS[i].rows, PATHS[i].colls);
		}
		cout << "TEXTURAS CARGADAS CORRECTAMENTE" << endl;
	}
	catch (exception e) {
		cout << "Error cargando texturas" << endl;
		exit = true;
	}
}

//Crea un arco y lo agrega a la lista de gameObjects
void Game::createBow() {
	Point2D pos;
	pos.setX(START_BOW_POS_X);
	pos.setY(BOW_POS_Y);
	Vector2D dir;
	int angle = 0, scale = 1;
	Bow* bow = new Bow(pos, dir, BOW_H, BOW_W, angle, scale, textures[BOW_1], this);
	gameObjects.push_back(bow);
	eventObjects.push_back(bow);
	bow = nullptr;
}

Texture* Game::getTextureBow(bool charged) {
	if (charged) return textures[BOW_1];
	else return textures[BOW_2];
}

void Game::mostrarGameObjects() {
	system("cls");
	cout << "LISTA DE GAMEOBJECTS:" << endl;
	for (int i = 0; i < gameObjects.size(); i++) {
		cout << "gameObjects.at(" << i << ") = " << gameObjects.at(i) << endl;
	}
}