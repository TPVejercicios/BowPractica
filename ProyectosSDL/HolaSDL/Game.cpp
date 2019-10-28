#include "Game.h"

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("First test with SDL", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr)
		cout << "Error cargando SDL" << endl;
	else
	{
		LoadPaths();
		////Carga texturas
		for (int i = 0; i < NUM_TEXTURES; i++) {
			Texture* aux = new Texture(renderer, images[i].path, images[i].rows, images[i].colls);
			textures.push_back(aux);
		}
		bow = new Bow(textures.at(1));

		//vector de ballons
	}
}

void Game::DeleteGame() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	//Llama a todos los destructores
}

void Game::run() {
	while (!exit) { // Falta el control de tiempo FRAME_
		SDL_Event current = handleEvents();
		if(current.type != SDL_QUIT){
			update(current);
			render();
			cout << "running" << endl;
		}
		else {
			cout << "Salir" << endl;
		}
	}
}

void Game::render() const {
	bow->render();
}

void Game::update(SDL_Event event) {
	bow->update(event);
	
}

void Game::throwArrow() {

}

void Game::createBallons() {

}

SDL_Event Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type == SDL_QUIT)
			exit = true;
		else if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_DOWN)		//tecla abajo
				cout << "ABAJO" << endl;
			else if (event.key.keysym.sym == SDLK_UP)	//tecla arriba
				cout << "ARRIBA" << endl;
			else if (event.key.keysym.sym == SDLK_LEFT)	//tecla izquierda
				cout << "Recarga" << endl;
		}
		else if (event.type == SDL_MOUSEBUTTONUP) {
			if (event.button.button == SDL_BUTTON_LEFT)
				cout << "TECLA DE RATON" << endl;
		}
	}
	return event;
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
 

