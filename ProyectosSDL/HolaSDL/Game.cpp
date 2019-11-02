#include "Game.h"

//Constructora, inicializa el juego y todos sus objetos
Game::Game() {				
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("First test with SDL", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr)
		cout << "Error cargando SDL" << endl;
	else
	{
		//Cargar imagenes del fichero
		LoadPaths();
		//Carga texturas
		try {
			for (int i = 0; i < NUM_TEXTURES; i++) {
				Texture* aux = new Texture(renderer, images[i].path, images[i].rows, images[i].colls);
				textures.push_back(aux);
				aux = nullptr;
			}
		}
		catch (exception e) {
			cout << loadingIMG << e.what() << endl;
			exit = true;
		}

		//Creación del bow
		try {
			bow = new Bow(textures.at(1), textures.at(2), textures.at(3));
		}
		catch (exception e) {
			cout << "Error creating bow " << e.what() << endl;
			exit = true;
		}


		//Creación del scoreboard
		try {
			scoreBoard = new ScoreBoard(textures.at(6), textures.at(4));
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
		//Llamo el destructor de cada globo y limpio el vector de globos
		for (int i = 0; i < ballons.size(); i++) delete ballons.at(i);
		ballons.clear();
		delete scoreBoard;
		delete bow;
		delete pointsPointer;
		delete backgroundPos;
		delete arrowHUD;
		//Llamo al destructor de cada textura 
		for (int i = 0; i < textures.size(); i++) delete textures.at(i);
		textures.clear();
		images.clear();
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
	textures.at(0)->render(*backgroundPos,SDL_FLIP_NONE);
	bow->render();

	for (int i = 0; i < ballons.size(); i++) {
		ballons.at(i)->render();
	}
	scoreBoard->render(points, bow->arrowsLeft());
	SDL_RenderPresent(renderer);
}

//Hace las llamadas a los updates de bow, arrow y a todos los globos
void Game::update() {
	bow->update();
	for (int i = 0; i < ballons.size(); i++) {
		if (ballons.at(i)->update())			//Si el update de ballon devuelve true destruyo el ballon
		{
			delete ballons.at(i);
			ballons.erase(ballons.begin() + i);
		}
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
			bow->handleEvents(event);
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

