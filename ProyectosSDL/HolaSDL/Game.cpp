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
		LoadPaths();
		//Carga texturas
		for (int i = 0; i < NUM_TEXTURES; i++) {
			Texture* aux = new Texture(renderer, images[i].path, images[i].rows, images[i].colls);
			textures.push_back(aux);
		}

		bow = new Bow(textures.at(1), textures.at(2), NUM_ARROWS);
		arrow = new Arrow(textures.at(3), textures.at(4), NUM_ARROWS);
	}
}

//Destructora
void Game::DeleteGame() {
	delete bow;
	delete arrow;
	for (int i = globos.size() - 1; i >= 0; i++) {
		delete globos.at(i);
		//globos.erase(globos.begin() + i);
	}
	globos.clear();
	//delete[] globos;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	//Llama a todos los destructores
}

//Bucle principal del juego
void Game::run() {				
	uint32_t startTime, frameTime, createBallon, ballonCreated;
	startTime = ballonCreated = SDL_GetTicks();
	while (!exit) {
		showPoints();
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
	bow->render(renderer);
	arrow->render(renderer);
	arrow->renderHUD(renderer);
	for (int i = 0; i < globos.size(); i++) {
		globos.at(i)->render(renderer);
	}
	SDL_RenderPresent(renderer); // Muestra la escena
}

//Hace las llamadas a los updates de bow, arrow y a todos los globos
void Game::update() {
	bow->update();
	arrow->update();
	for (int i = 0; i < globos.size(); i++) {
		if (globos.at(i)->update())
		{
			delete globos.at(i);
			globos.erase(globos.begin() + i);
		}
	}
}

//Crea un globo y lo mete al vector de globos
void Game::createBallons() {
	Ballon* aux = new Ballon(textures.at(5), this);
	globos.push_back(aux);
}

//Hace la llamada a los eventos de arrow y bow
void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type != SDL_QUIT) {
			bow->handleEvents(event);
			arrow->handleEvents(event, bow->devuelvePosY());
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

	if (arrow->getDisparada()) {
		for (int i = 0; i < globos.size(); i++) {
			if (globos.at(i)->returnState() && SDL_HasIntersection(globos.at(i)->returnBallonBody() , arrow->returnArrowHead())) {
				points += 10;
				globos.at(i)->ballonPunctured(SDL_GetTicks());
			}
		}
	}
}
 

