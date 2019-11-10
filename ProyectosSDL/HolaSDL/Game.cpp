#include "Game.h"

//Constructora, inicializa el juego y todos sus objetos
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
		try {
			loadTextures();
		}
		catch (exception e) {
			cout << loadingIMG << e.what() << endl;
			exit = true;
		}

		//Creación del bow
		try {
			/*Bow* bow = new Bow(_pos, _angle, _scale, _game, textures.at(2) , _body);
			gameObjects.push_back(bow);
			bow = nullptr;*/
		}
		catch (exception e) {
			cout << "Error creating bow " << e.what() << endl;
			exit = true;
		}


		//Creación del scoreboard
		try {
			
		}
		catch (exception e) {
			cout << "Error creating scoreBoard " << e.what() << endl;
			exit = true;
		}
			
	}
}

//Destructora, llama a todos los destructores de la clase game
Game::~Game() {
	try {
		//Llamo al destructor virtual de cada tipo de objeto (nose si esto se hace así)
		for (int i = gameObjects.size(); i > 0; i--) {
			delete gameObjects.at(i);
			gameObjects.pop_back();
		}
		////llamo el destructor de cada globo y limpio el vector de globos
		//for (int i = 0; i < ballons.size(); i++) delete ballons.at(i);
		//ballons.clear();
		//delete scoreboard;
		//delete bow;
		//delete pointspointer;
		//delete backgroundpos;
		//delete arrowhud;
		//Llamo al destructor de cada textura 
		for (int i = 0; i < textures.size(); i++) delete textures.at(i);
		textures.clear();
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		cout << "Se han destruido todos los elementos del juego" << endl;
	}
	catch (exception e) {
		cout << deletingOBJ << e.what() << " ::game class:: " << endl;
	}

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
			startTime = SDL_GetTicks();
		}
		if (createBallon >= FRAME_BALLON) {
			createBallons();
			ballonCreated = SDL_GetTicks();
		}

	}
	cout << "Fin del juego" << endl;
}

//Dibuja cada objeto en el SDL_Renderer
void Game::render() {		
	SDL_RenderClear(renderer);
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects.at(i)->update();
	}
	SDL_RenderPresent(renderer);
}

//Hace las llamadas a los updates de todos los objetos del juego
void Game::update() {
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects.at(i)->update();
	}
}

//Crea un globo y lo mete al vector de globos
void Game::createBallons() {
	Ballon* currBallon = new Ballon(textures.at(5), this);
	ballons.push_back(currBallon);
	currBallon = nullptr;
}

//Hace la llamada a los eventos de arrow y bow
void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type != SDL_QUIT) {
			//bow->handleEvents(event);
		}
		else exit = true;
	}
}

//Comprueba si una flecha a colisionado contra un globo
void Game::checkCrushBallon() {
	if (bow->bowShoted()) {
		for (int i = 0; i < ballons.size(); i++) {
			for (int j = 0; j < bow->arrowShooted(); j++) {
				if (ballons.at(i)->returnState() && SDL_HasIntersection(ballons.at(i)->returnBallonBody(), bow->returnArrowHeadBow(j))) {
					points += 10;
					ballons.at(i)->ballonPunctured();
				}
			}

		}
	}
}

//Carga las texturas en un vector
void Game::loadTextures() {
	for (int i = 0; i < NUM_TEXTURES; i++) {
		Texture* aux = new Texture(renderer, PATHS[i].filename, PATHS[i].rows, PATHS[i].colls);
		textures.push_back(aux);
		aux = nullptr;
	}
}

