#include "Game.h"

void Game::DeleteGame() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	//Llama a todos los destructores
}

void Game::run() {

	while (!exit) { // Falta el control de tiempo FRAME_
		handleEvents();
		update();
		render();
	}
}

void Game::render() const {

}

void Game::update() {

}

void Game::throwArrow() {

}

void Game::createBallons() {

}

void Game::handleEvents() {
	SDL_Event event;

	while (!exit) {
		while (SDL_PollEvent(&event) && !exit) {
			if (event.type == SDL_QUIT)
				exit = true;
			else if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_DOWN)		//tecla abajo
					cout << "ABAJO" << endl;
				else if (event.key.keysym.sym == SDLK_UP)	//tecla arriba
					cout << "ARRIBA" << endl;
			}
			else if (event.type == SDL_MOUSEBUTTONUP) {
				if (event.button.button == SDL_BUTTON_LEFT) 
					cout << "TECLA DE RATON" << endl;

			}
		}
	}
}

//Carga las imagenes individualmente
void Game::LoadPaths() {
	image aux;
	//BACKGROUND
	aux.path = PATHS[0];
	aux.colls = aux.rows = 1;
	images.push_back(aux);
	
	//BOW1
	aux.path = PATHS[1];
	aux.colls = aux.rows = 1;
	images.push_back(aux);
	//BOW2
	aux.path = PATHS[2];
	aux.colls = aux.rows = 1;
	images.push_back(aux);
	//ARROW1
	aux.path = PATHS[3];
	aux.colls = aux.rows = 1;
	images.push_back(aux);
	//ARROW2
	aux.path = PATHS[4];
	aux.colls = aux.rows = 1;
	images.push_back(aux);
	//BALLONS
	aux.path = PATHS[5];
	aux.colls = 6;
	aux.rows = 7;
	images.push_back(aux);
	//DIGITS
	aux.path = PATHS[6];
	aux.colls = 10;
	aux.rows = 1;
	images.push_back(aux);
}



