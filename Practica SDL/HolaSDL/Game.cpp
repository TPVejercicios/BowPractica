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
		loadTextures();
		loadLevel();
		createBow();
		//createScoreBoard();
	}
}

//Destructora, llama a todos los destructores de la clase game 
Game::~Game() {
	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) delete* it;
	for (int i = 0; i < NUM_TEXTURES; i++) delete textures[i];
	gameObjects.clear();
	eventObjects.clear();
	arrows.clear();
	delete background;
	background = nullptr;
	SCB = nullptr;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

//Bucle principal del juego
void Game::run() {
	uint32_t startTime, frameTime, createBallon, ballonCreated;
	startTime = ballonCreated = SDL_GetTicks();
	while (!exit && !endGame()) {
		handleEvents();
		createBallon = SDL_GetTicks() - ballonCreated;
		frameTime = SDL_GetTicks() - startTime;
		if (frameTime >= FRAME_RATE) {
			update();
			render();	
			checkCollisions();
			deleteObjects();
			//info();
			//mostrarGameObjects(); //Auxiliar para debug
			startTime = SDL_GetTicks();
		}
		if (createBallon >= LEVELS[currLevel].frame_ballon) {
			createBallons();
			ballonCreated = SDL_GetTicks();
		}
		//exit = endGame();
	}
	cout << "Fin del juego" << endl;
}

//Llama a los eventos de los eventObjects
void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type != SDL_QUIT) {
			for (auto eventIT = eventObjects.begin(); eventIT != eventObjects.end(); ++eventIT) {
				auto* aux = dynamic_cast<EventHandler*>(*eventIT);
				(aux)->handleEvent(event);
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
	int angle = 0, scale = 1;
	Arrow* arrow = new Arrow(_pos, {1,0}, ARROW_H, ARROW_W, angle, scale, textures[ARROW_1], this,ARROW_ID);
	gameObjects.push_back(arrow);
	arrows.push_back(arrow);
	arrow = nullptr;
}

void Game::mostrarGameObjects() {
	system("cls");
	cout << "Elementos en gameObject	: " << gameObjects.size() << endl;
	cout << "Elementos en objectToErase	: " << objectsToErase.size() << endl;
	cout << "Elementos en arrows		: " << arrows.size() << endl;
}

//Borra un elemento en las distintas listas en la que puede estar, se distinguen dos casos
//		*Para borrar una mariposa o un globo se debe eliminar en gameObjects y objectsToErase
//		*Para borrar una flecha se debe eliminar de gameObjects, objectsToErase y de arrows

void Game::deleteObjects() {
	auto OTEIT = objectsToErase.begin();
	while (OTEIT != objectsToErase.end()) {
		auto GOIT = gameObjects.begin();
		bool found = false;
		while (!found && GOIT != gameObjects.end()){
			if ((*OTEIT) == (*GOIT)) {								//Coincidencia entre objectToErase y gameObject
				//cout << "Se encontro coincidencia GO:" << gameObjects.size() << " OTE: " << objectsToErase.size() << endl;
				auto* aux_is_arrow = dynamic_cast<Arrow*>(*OTEIT);			//Eres una flecha?
				auto* aux_is_event = dynamic_cast<EventHandler*>(*OTEIT);
				if (aux_is_arrow != nullptr) {							//También debe eliminarse de arrows
					//cout << "Se detecto una flecha " << arrows.size() <<  endl;
					auto ARWIT = arrows.begin();
					bool arrowFounded = false;
					while (!arrowFounded && ARWIT != arrows.end())
					{
						if ((*OTEIT) == (*ARWIT)) {
							arrows.erase(ARWIT);
							arrowFounded = true;
							//cout << "Se elimino flecha " <<arrows.size()  <<  endl;
						}
						else {
							ARWIT++;
						}
					}
				}
				else if (aux_is_event != nullptr) {							//También debe eliminarse de arrows
					//cout << "Se detecto un evento " << arrows.size() <<  endl;
					auto EHIT = eventObjects.begin();
					bool eventFounded = false;
					while (!eventFounded && EHIT != eventObjects.end())
					{
						if ((*OTEIT) == (*EHIT)) {
							eventObjects.erase(EHIT);
							eventFounded = true;
							cout << "Se elimino evento " <<arrows.size()  <<  endl;
						}
						else {
							EHIT++;
						}
					}
				}
				auto auxIT = GOIT;
				auto auxEIT = OTEIT;
				GameObject* gm = *GOIT;
				OTEIT++;
				GOIT++;
				objectsToErase.erase(auxEIT);
				gameObjects.erase(auxIT);
				delete (gm);
				found = true;
				//cout << "Se borro el elemento GO:" << gameObjects.size() << " OTE: " << objectsToErase.size() << endl;

			}
			else
			{
				GOIT++;
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
	SCB = new ScoreBoard(textures[DIGITS], textures[ARROW_2], currPoints, currArrows, this);
	gameObjects.push_back(SCB);
}

void Game::createReward(Point2D _pos) {
	//Point2D _pos, Vector2D _dir, int _h, int _w, int _angle, int _scale, Texture* _bubleTex,Texture* reward_tex, Game* _game,int _id
	int rnd = rand() % MAX_REWARDS;
	Reward* currReward = nullptr;
	switch (rnd)
	{
	case 0:
		currReward = new AddArrows(_pos, {0,1},REWARD_H,REWARD_W,0,1,textures[BUBBLE],this,textures[REWARDS],OBJECT_REWARD);
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	default:
		break;
	}
	currReward = new AddArrows(_pos, { 0,1 }, REWARD_H, REWARD_W, 0, 1, textures[BUBBLE], this, textures[REWARDS], OBJECT_REWARD);
	if (currReward != nullptr) {
		gameObjects.push_back(currReward);
		eventObjects.push_back(currReward);
		currReward = nullptr;
	}
}

//Comprueba las collisiones entre las arrows y los gameObjects(Luego cambiar a preguntar si tiene un handleEvent)
void Game::checkCollisions() {
	for (auto arrowIT = arrows.begin(); arrowIT != arrows.end(); ++arrowIT) {
		for (auto gameObIT = gameObjects.begin(); gameObIT != gameObjects.end(); ++gameObIT) {
			auto* currGO = dynamic_cast<ArrowGameObject*>(*gameObIT);
			SDL_Rect rc = (*arrowIT)->getRectForCollision();		//Esto no me funciona en el hasInterrsection
			if (currGO != nullptr && currGO->isCollisionable() && SDL_HasIntersection(&currGO->getRect(),&rc ))
			{
				switch (currGO->getID())
				{
				case BALLON_ID:
					(*arrowIT)->AddStack();
					break;
				case BUTTERFLY_ID:
					if (currPoints - POINTS_TO_SUB < 0) currPoints = 0;			//Nunca se obtiene una puntuación negativa
					else currPoints -= POINTS_TO_SUB;
					cout << "Se restan = " << POINTS_TO_SUB << " total = " << currPoints << endl;
					currButterflies--;
					cout << "Mariposa eliminada quedan : " << currButterflies << endl;
					SCB->updatePoints(currPoints);
					break;
				case OBJECT_REWARD:
					

				default:
					break;
				}
				nextLevel();
				currGO->startDestruction();
			}
		}
	}
}

//Crea butterflies y las agrega al la lista de mariposas
void Game::createButterfly() {
	for (int i = 0; i < LEVELS[currLevel].butterflyNum; i++) {
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

//Carga el nivel(fondo,mariposas y flechas)
void Game::loadLevel() {
	cout << "Cargado el nivel : " << currLevel << endl;
	background = new Background(WIN_HEIGHT, WIN_WIDTH, textures[LEVELS[currLevel].currTex]);
	currButterflies = LEVELS[currLevel].butterflyNum;
	cout << "Entran " << currButterflies << " mariposas." << endl;
	currArrows += LEVELS[currLevel].arrows; 
	cout << "Se recargan " << LEVELS[currLevel].arrows << " de flechas, total " << currArrows << endl;
	createButterfly();
	createScoreBoard();
}

//Comprueba si se han superado los puntos necesarios para cargar el siguiente nivel y los carga si es efectivo
void Game::nextLevel() {
	if (currLevel < MAX_LEVELS && currPoints >= LEVELS[currLevel].pointsToReach) {
		currLevel++;
		killObject(SCB);
		deleteAllbutterflies();
		deleteAllBallons();
		deleteAllArrows();
		//deleteAllEvents();
		loadLevel();
	}
}

//Manda a destruir todas las butterflies que estan en escena
void Game::deleteAllbutterflies() {
	if (currButterflies > 0) {
		cout << "Se borran todas las mariposas que quedaron en la escena" << endl;
		for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
			auto aux = dynamic_cast<Butterfly*>(*it);
			if (aux != nullptr && !aux->isDeleting()) {
				killObject(aux);
			}
			aux = nullptr;
		}
	}
}

//Manda a destruir todos los eventos que se hayan quedado en la escena

//Manda a eleminar todas las flechas que pudieron quedarse en la escena
void Game::deleteAllArrows() {
	cout << "Se borran todas las flechas que quedaron en la escena" << endl;
	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
		auto aux = dynamic_cast<Arrow*>(*it);
		if (aux != nullptr && !aux->isDeleting()) {
			killObject(aux);
		}
	}
}

//Manda a destruir todas los ballons que estan en escena
void Game::deleteAllBallons() {
	cout << "Se borran todos los globos que quedaron en la escena" << endl;
	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
		auto aux = dynamic_cast<Ballon*>(*it);
		if (aux != nullptr && !aux->isDeleting()) {
			killObject(aux);
		}
	}
}

void Game::info() {
	system("cls");
	cout << "BUT	: " << currButterflies << endl;
	cout << "POINTS : " << currPoints << endl;
}

//Multiplica los puntos por cada globo que una flecha haya destruido
void Game::arrowStacks(int _stacks) {
	currPoints += _stacks * POINTS_TO_ADD;
	cout << "stacks! : " << _stacks << " // puntos = " << currPoints << " // Puntos agregados : " << _stacks * POINTS_TO_ADD << endl;
	SCB->updatePoints(currPoints);
}

//Comprueba el jugador a perdido el juego
bool Game::endGame() {
	bool gameOver = false;
	if (currButterflies == 0) {
		gameOver = true;
		cout << "Has matado todas las mariposas " << endl;
	}
	else if (arrows.empty() && currArrows == 0 && !bowCharged) {
		gameOver = true;
		cout << "Te has quedado sin flechas" << endl;
	}
	return gameOver;
}

//Devuelve la textura de cargado o descargado al bow
Texture* Game::getTextureBow(bool _charged) {

	if (_charged) {
		bowCharged = true;
		currArrows--;
		SCB->updateArrows(currArrows);
	}
	else bowCharged = false;
	return _charged ? textures[BOW_1] : textures[BOW_2];
}


