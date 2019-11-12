#include "Game.h"




using namespace std;

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
		loadTextures();

		ArrowGameObject* Bg = new Background(textures.at(2),this);
		gameObjects.push_back(Bg);
		Bg = nullptr;

		//Creación del bow //9
		try {
			ArrowGameObject* bow = new Bow(textures.at(9), textures.at(10), textures.at(0), this);
			gameObjects.push_back(bow);
			bow = nullptr;
		}
		catch (exception e) {
			cout << "Error creating bow " << e.what() << endl;
			exit = true;
		}


		//Creación del scoreboard
		try {
			ArrowGameObject* scoreBoard = new ScoreBoard(textures.at(13),textures.at(1),this);
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

//Crea un globo y lo mete al vector de globos
void Game::createBallons() {
	Ballon* currBallon = new Ballon(textures.at(8), this);
	gameObjects.push_back(currBallon);
	currBallon = nullptr;
}

//Hace la llamada a los eventos de arrow y bow
void Game::handleEvents() {
	SDL_Event event;
	int contador = 0;
	while (SDL_PollEvent(&event) && !exit) {

		if (event.type != SDL_QUIT)
		{
			dynamic_cast<EventHandler*>(gameObjects.at(1))->handleEvent(event);
		}
		else
		{
			exit = true;
		}
		
	}
}

//Comprueba si una flecha a colisionado contra un globo
void Game::checkCrushBallon(SDL_Rect* arrowColl ) {

	//SDL_Rect* currBallon = new SDL_Rect();
	Ballon* currBallon;

	for (int i = 0; i < gameObjects.size(); i++) {

		if (dynamic_cast<Ballon*>(gameObjects.at(i)) && 
			SDL_HasIntersection(dynamic_cast<ArrowGameObject*>(gameObjects.at(i))->getCollisionRect(),arrowColl)){

			points += 10;
			dynamic_cast<Ballon*>(gameObjects.at(i))->ballonPunctured();
		}

	}
}

//Carga las texturas en un vector (couts for debug)
void Game::loadTextures() {
	Texture* aux = nullptr;
	try {
		cout << "Intentamos cargar texturas" << endl;
		for (int i = 0; i < NUM_TEXTURES; i++) {
			aux = new Texture(renderer, PATHS[i].filename, PATHS[i].rows, PATHS[i].colls);
			textures.push_back(aux);
			
			//delete aux;
			cout << "Textura(" << i << ") cargada" << endl;
		}
		cout << "TEXTURAS CARGADAS CORRECTAMENTE" << endl;
	}
	catch (exception e) {
		cout << loadingIMG << endl;
		exit = true;
	}
	aux = nullptr;
}



