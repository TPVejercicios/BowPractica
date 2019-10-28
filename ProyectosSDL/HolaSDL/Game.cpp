#include "Game.h"

Game::Game() {				//Constructora, inicializa el juego y todos sus objetos
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("First test with SDL", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr)
		cout << "Error cargando SDL" << endl;
	else
	{
		LoadPaths();
		//Carga texturas
		for (int i = 0; i < NUM_TEXTURES; i++) {
			Texture* aux = new Texture(renderer, images[i].path, images[i].rows, images[i].colls);
			textures.push_back(aux);
		}
		bow = new Bow(textures.at(1), textures.at(2), NUM_ARROWS);
		arrow = new Arrow(textures.at(3), textures.at(4), NUM_ARROWS);

		//vector de ballons
	}
}

void Game::DeleteGame() {		//Destructora
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	//Llama a todos los destructores
}

void Game::run() {				//Bucle principal del juego
	while (!exit) { // Falta el control de tiempo FRAME_
		handleEvents();
		update();
		render();
	}
	cout << "Fin del juego" << endl;
}

void Game::render() const {		//Dibuja cada objeto en el SDL_Renderer
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, textures.at(0)->getTexture(), nullptr, nullptr); // Copia en buffer
	bow->render(renderer);
	arrow->render(renderer);
	arrow->renderHUD(renderer);
	/*for (int i = 0; i < ballons.size; i++) {
		ballons.at(i)->render(renderer);
	}*/
	SDL_RenderPresent(renderer); // Muestra la escena
}

void Game::update() {
	bow->update();
	arrow->update();
	/*for (int i = 0; i < ballons.size; i++) {
		ballons.at(i)->update();
	}*/
}

void Game::throwArrow() {

}

void Game::createBallons() {

}

void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type != SDL_QUIT) {
			bow->handleEvents(event);
			arrow->handleEvents(event, bow->devuelvePosY());
			/*for (int i = 0; i < ballons.size; i++) {
				ballons.at(i)->handleEvents(event);
			}*/
		}
		else exit = true;
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
 

