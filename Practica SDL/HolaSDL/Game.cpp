#include "Game.h"



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
		//Crea el background
		background = new Background(WIN_HEIGHT, WIN_WIDTH, textures[BG_4]);
		createBow();
		createScoreBoard();
		createButterfly();
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
			checkCollisions();
			deleteObjects();
			//mostrarGameObjects(); //Auxiliar para debug
			startTime = SDL_GetTicks();
		}
		if (createBallon >= FRAME_BALLON) {
			createBallons();
			ballonCreated = SDL_GetTicks();
		}

	}
	cout << "Fin del juego" << endl;
}

//Llama a los eventos de los eventObjects
void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type != SDL_QUIT) {
			for (auto eventIT = eventObjects.begin(); eventIT != eventObjects.end(); ++eventIT) {
				(*eventIT)->handleEvent(event);
			}
		}
		else exit = true;
	}
}

//Dibuja cada objeto en el SDL_Renderer
void Game::render() {
	SDL_RenderClear(renderer);
	background->render();
	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
		(*it)->render();
	}
	SDL_RenderPresent(renderer);
}

//Hace las llamadas a los updates de todos los objetos del juego
void Game::update() {
	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
		(*it)->update();
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

//Crea un arco y lo agrega a la lista de gameObjects y de eventsObjects
void Game::createBow() {
	Point2D pos;
	pos.setX(START_BOW_POS_X);
	pos.setY(BOW_POS_Y);
	Vector2D dir;
	int angle = 0;
	Bow* bow = new Bow(pos, dir, BOW_H, BOW_W, angle, BOW_SCALE, textures[BOW_1], this,BOW_ID);
	gameObjects.push_back(bow);
	eventObjects.push_back(bow);
	bow = nullptr;
}

//Crea una arrow y la agrega a gameObjects y arrows
void Game::createArrow(Vector2D _pos) {
	remainingShots--;
	int angle = 0, scale = 1;
	Arrow* arrow = new Arrow(_pos, {1,0}, ARROW_H, ARROW_W, angle, scale, textures[ARROW_1], this,ARROW_ID);
	gameObjects.push_back(arrow);
	arrows.push_back(arrow);
	arrow = nullptr;
	SCB->updateArrowHUD();
}

void Game::mostrarGameObjects() {
	system("cls");
	cout << "elementos en gameObject: " << gameObjects.size() << endl;
	cout << "Elementos en objectToErase: " << objectsToErase.size() << endl;
}

//Falta borrarlo de gameObjects y arrowGameobjects
void Game::deleteObjects() {
	auto it = objectsToErase.begin();
	while (it != objectsToErase.end())
	{
		auto gIT = gameObjects.begin();
		bool found = false;
		while (!found && gIT != gameObjects.end())
		{
			if ((*it) == (*gIT)) {
				auto auxIT = gIT;
				auto auxEIT = it;
				GameObject* gm = *gIT;
				it++;
				objectsToErase.erase(auxEIT);
				gameObjects.erase(auxIT);
				delete (gm);
				found = true;
			}
			else
			{
				gIT++;
			}
		}
	}
}

//Crea un globo y lo agrega a la lista de gameObjects
void Game::createBallons() {
	Point2D _pos;
	_pos.setX(rand()%(BALLON_MAX_POS_X - BALLON_MIN_POS_X) + BALLON_MIN_POS_X);
	_pos.setY(BALLON_MIN_POS_Y);
	Vector2D _dir;
	_dir.setY(1);
	int _speed = rand() % (BALLON_MAX_SPEED - BALLON_MIN_SPEED) + BALLON_MIN_SPEED;
	Ballon* currBallon = new Ballon(_pos, _dir, BALLON_H, BALLON_W ,0, 1, textures[BALLONS], this,_speed,BALLON_ID);
	gameObjects.push_back(currBallon);
	currBallon = nullptr;
}

//Crea un scoreBoard y lo agrega a gameObjects
void Game::createScoreBoard() {
	ScoreBoard* scb = new ScoreBoard(textures[DIGITS],textures[ARROW_2], this);
	gameObjects.push_back(scb);
	SCB = scb;
	scb = nullptr;
}

//Comprueba las collisiones entre las arrows y los gameObjects(Luego cambiar a preguntar si tiene un handleEvent)
void Game::checkCollisions() {
	for (auto arrowIT = arrows.begin(); arrowIT != arrows.end(); ++arrowIT) {
		for (auto gameObIT = gameObjects.begin(); gameObIT != gameObjects.end(); ++gameObIT) {
			ArrowGameObject* aux = dynamic_cast<ArrowGameObject*>(*gameObIT);
			SDL_Rect rc = (*arrowIT)->getRectForCollision();		//Esto está mal lo sé, es un apaño :D
			if (aux != nullptr && SDL_HasIntersection(&aux->getRect(),&rc ))
			{
				switch (aux->getID())
				{
				case BALLON_ID:
					points += POINTS_TO_ADD;
					aux->startDestruction();
					(*arrowIT)->AddStack();
					break;
				case BUTTERFLY_ID:
					points -= POINTS_TO_SUB;
					aux->startDestruction();
					break;
				default:
					break;
				}
			}
		}
	}
}

void Game::createButterfly() {
	for (int i = 0; i < 15; i++) {
		Point2D _pos;
		_pos.setX(rand() % (BUTT_MAX_X - BUTT_MIN_X) + BUTT_MIN_X);
		_pos.setY(rand() % WIN_HEIGHT);
		Vector2D _dir;
		_dir.setX(rand() % -2 + 1);
		_dir.setY(rand() % -2 + 1);
		Butterfly* currButterfly = new Butterfly(_pos, _dir, BUTTERFLY_H, BUTTERFLY_W, 0, 1, textures[BUTTERFLY], this, BUTTERFLY_ID);
		gameObjects.push_back(currButterfly);
		currButterfly = nullptr;
	}
}
