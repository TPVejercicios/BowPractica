#include "Game.h"
#include <math.h>

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
		LoadPaths();
		//Carga texturas
		for (int i = 0; i < NUM_TEXTURES; i++) {
			Texture* aux = new Texture(renderer, images[i].path, images[i].rows, images[i].colls);
			textures.push_back(aux);
			aux = nullptr;
		}
		bow = new Bow(textures.at(1), textures.at(2), textures.at(3), textures.at(4), NUM_ARROWS);
		//Carga scala de puntajes
		firstPointer = new SDL_Rect();
		secondPointer = new SDL_Rect();
		thirdPointer = new SDL_Rect();
		firstPointer->h = firstPointer->w = POINTS_SCALE;
		secondPointer->h = secondPointer->w = POINTS_SCALE;
		thirdPointer->h = thirdPointer->w = POINTS_SCALE;
		firstPointer->x = 150; firstPointer->y = 0;
		secondPointer->x = 120; secondPointer->y = 0;
		thirdPointer->x = 90; thirdPointer->y = 0;
	}
}

//Destructora, llama a todos los destructores de la clase game
Game::~Game() {
	//Llamo el destructor de cada globo y limpio el vector de globos
	for (int i = 0; i < globos.size(); i++) delete globos.at(i);
	globos.clear();
	//Llamo al destructor de cada textura y limpio el vector de globos
	for (int i = 0; i < textures.size(); i++) textures.at(i)->liberar();
	textures.clear();
	delete bow;
	delete firstPointer;
	delete secondPointer;
	delete thirdPointer;
	images.clear();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

//Bucle principal del juego
void Game::run() {				
	uint32_t startTime, frameTime, createBallon, ballonCreated;
	startTime = ballonCreated = SDL_GetTicks();
	while (!exit) {
		updatePoints();
		handleEvents();
		createBallon = SDL_GetTicks() - ballonCreated;
		frameTime = SDL_GetTicks() - startTime;
		if (frameTime >= FRAME_RATE) {
			update();
			startTime = SDL_GetTicks();
		}
		if (createBallon >= FRAME_BALLON) {
			createBallons();
			ballonCreated = SDL_GetTicks();
		}
		render();
	}
	cout << "Fin del juego" << endl;
}

//Dibuja cada objeto en el SDL_Renderer
void Game::render() const {		
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, textures.at(0)->getTexture(), nullptr, nullptr); // Copia en buffer
	bow->render();
	renderPoints();
	for (int i = 0; i < globos.size(); i++) {
		globos.at(i)->render();
	}
	SDL_RenderPresent(renderer); // Muestra la escena
}

//Hace las llamadas a los updates de bow, arrow y a todos los globos
void Game::update() {
	bow->update();
	updatePoints();
	for (int i = 0; i < globos.size(); i++) {
		if (globos.at(i)->update())			//Si el update de ballon devuelve true destruyo el ballon
		{
			delete globos.at(i);
			globos.erase(globos.begin() + i);
		}
	}
}

//Crea un globo y lo mete al vector de globos
void Game::createBallons() {
	Ballon* currBallon = new Ballon(textures.at(5), this);
	globos.push_back(currBallon);
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
	if (bow->getDisparadaBow()) {
		for (int i = 0; i < globos.size(); i++) {
			if (globos.at(i)->returnState() && SDL_HasIntersection(globos.at(i)->returnBallonBody() , bow->returnArrowHeadBow())) {
				points += 10;
				globos.at(i)->ballonPunctured();
			}
		}
	}
}

//Actualiza el valor del iterador de cada rect del puntaje
void Game::updatePoints() {
	string pointsString = to_string(points);
	//48 es el valor a restar para convertir char en int (Codigo ASCII)
	if (points < 10) {
		first = points;
	}
	else if (points < 100) {
		first =  ((int)(pointsString[1]) - 48);		
		second = ((int)(pointsString[0]) - 48);
	}
	else
	{
		first = ((int)(pointsString[2]) - 48);
		second = ((int)(pointsString[1]) - 48);
		third = ((int)(pointsString[0]) - 48);
	}



}

//Renderiza el puntaje
void Game::renderPoints() const {
	textures.at(6)->renderFrame(*firstPointer, 0,first, 0, SDL_FLIP_NONE);
	textures.at(6)->renderFrame(*secondPointer, 0, second, 0, SDL_FLIP_NONE);
	textures.at(6)->renderFrame(*thirdPointer, 0,third , 0, SDL_FLIP_NONE);
}




 

