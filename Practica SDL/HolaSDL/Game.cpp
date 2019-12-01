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
		srand(time(NULL));
		loadTextures();
		loadLevel();
		createBow();
	}
}

Game::Game(int n) {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Practica2", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr)
		cout << "Error cargando SDL" << endl;
	else
	{
		srand(time(NULL));
		loadTextures();
		cout << "Cargando " << n << ".txt" << endl;
		loadGame(n);
	}
}

void Game::loadGame(int name) {
	//ofstream partida(to_string(n) + "txt");
	ifstream partida (to_string(name) + ".txt");
	Bow* bow;
	Arrow* arrow;
	Ballon* ballon;
	Butterfly* butterfly;
	Reward* reward;
	if (partida.is_open()) {
		int N = 0;	//Numero de enemigos
		string aux;
		int intaux;
		int id_object;
		int posx, posy, dirx, diry, other;
		partida >> aux; //nivel
		partida >> aux; //dato
		currLevel = stoi(aux);
		partida >> aux;	//points
		partida >> aux;	//dato
		currPoints = stoi(aux);
		partida >> aux; //arrows
		partida >> aux; //dato
		currArrows = stoi(aux);
		partida >> aux;	//butterflies
		partida >> aux;	//dato
		currButterflies = stoi(aux);
		partida >> aux; //bScale
		partida >> aux; //dato
		ballonScale = stoi(aux);
		partida >> aux;	//bowCharged
		partida >> aux;	//dato
		intaux = stoi(aux);
		if (intaux == 1) bowCharged = true;
		else bowCharged = false;
		partida >> aux;	//dato
		N = stoi(aux);
		cout << "N es " << N << endl;
		for (int i = 0; i < N; i++) { //Para crear cada objeto
			partida >> aux; //id
			if (aux == "id") {	//Si la linea del objeto no empieza por id es que ese objeto es un Objeto No Cargable
				partida >> aux;
				id_object = stoi(aux);
				cout << "Objeto" << i << " con id " << id_object << endl;
				partida >> aux;	//posx
				partida >> aux;	//dato
				posx = stoi(aux);
				partida >> aux;	//posy
				partida >> aux;	//dato
				posy = stoi(aux);
				partida >> aux;	//dirx
				partida >> aux;	//dato
				dirx = stoi(aux);
				partida >> aux;	//diry
				partida >> aux;	//dato
				diry = stoi(aux);
				partida >> aux;	//other
				partida >> aux;	//dato
				other = stoi(aux);
				//La idea es coger ahora todos los datos de cada objeto y crearlos dentro del switch
				switch (id_object) {
				case OBJECT_BOW:
					if (other == 0) currArrows--;	//Entra a este if si el arco se guardó sin cargar, con lo cual le quitamos una flecha y lo metemos cargado 
					bow = new Bow({ START_BOW_POS_X, posy }, { dirx, diry }, BOW_H, BOW_W, 0, BOW_SCALE, textures[BOW_1], this, BOW_ID);
					gameObjects.push_back(bow);
					eventObjects.push_back(bow);
					bow = nullptr;
					break;
				case OBJECT_ARROW:
					arrow = new Arrow({ posx, posy }, { dirx, diry }, ARROW_H, ARROW_W, 0, 1, textures[ARROW_1], this, ARROW_ID);
					gameObjects.push_back(arrow);
					arrows.push_back(arrow);
					arrow = nullptr;
					break;
				case OBJECT_BALLON:
					ballon = new Ballon({ posx, posy }, { dirx, diry }, BALLON_H, BALLON_W, 0, ballonScale, textures[BALLONS], this, other, BALLON_ID);
					gameObjects.push_back(ballon);
					ballon = nullptr;
					break;
				case OBJECT_BUTTERFLY:
					butterfly = new Butterfly({ posx, posy }, { dirx, diry }, BUTTERFLY_H, BUTTERFLY_W, 0, 1, textures[BUTTERFLY], this, BUTTERFLY_ID);
					gameObjects.push_back(butterfly);
					butterfly = nullptr;
					break;
				case OBJECT_REWARD: 
					reward = nullptr;
					switch (other)
					{
					case 0:
						reward = new AddArrows({ posx, posy }, { dirx, diry }, REWARD_H, REWARD_W, 0, 1, textures[BUBBLE], this, textures[REWARDS], OBJECT_REWARD);
						break;
					case 1:
						reward = new RemoveArrows({ posx, posy }, { dirx, diry }, REWARD_H, REWARD_W, 0, 1, textures[BUBBLE], this, textures[REWARDS], OBJECT_REWARD);
						break;
					case 2:
						reward = new ReviveButterflies({ posx, posy }, { dirx, diry }, REWARD_H, REWARD_W, 0, 1, textures[BUBBLE], this, textures[REWARDS], OBJECT_REWARD);
						break;
					case 3:
						reward = new BigBallons({ posx, posy }, { dirx, diry }, REWARD_H, REWARD_W, 0, 1, textures[BUBBLE], this, textures[REWARDS], OBJECT_REWARD);
						break;
					default:
						break;
					}
					gameObjects.push_back(reward);
					eventObjects.push_back(reward);
					reward = nullptr;
				}
			}
		}
		background = new Background(WIN_HEIGHT, WIN_WIDTH, textures[LEVELS[currLevel].currTex]);
		SCB = new ScoreBoard(textures[DIGITS], textures[ARROW_2], currPoints, currArrows, this);
		gameObjects.push_back(SCB);
		cout << "Objetos cargados correctamente";
	}
	else throw new exception;
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
	while (!exit) {
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
		endGame();
	}
	cout << "Fin del juego" << endl;
}

//Llama a los eventos de los eventObjects
void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type != SDL_QUIT) {
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_s) {
				int partida;
				cout << "Introduce el nombre con el que quieres guardar el archivo(solo numeros): ";
				cin >> partida;
				saveGame(partida);
			}
			else {
				for (auto eventIT = eventObjects.begin(); eventIT != eventObjects.end(); ++eventIT) {
					auto* aux = dynamic_cast<EventHandler*>(*eventIT);
					(aux)->handleEvent(event);
				}
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
	Bow* bow = new Bow(pos, dir, BOW_H, BOW_W, angle, BOW_SCALE, textures[BOW_1], this, BOW_ID);
	gameObjects.push_back(bow);
	eventObjects.push_back(bow);
	bow = nullptr;
}

//Crea una arrow y la agrega a gameObjects y arrows
void Game::createArrow(Vector2D _pos) {
	int angle = 0, scale = 1;
	Arrow* arrow = new Arrow(_pos, {1,0}, ARROW_H, ARROW_W, angle, scale, textures[ARROW_1], this, ARROW_ID);
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
	Ballon* currBallon = new Ballon(_pos, _dir, BALLON_H, BALLON_W ,0, ballonScale, textures[BALLONS], this,_speed,BALLON_ID);
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
		currReward = new RemoveArrows(_pos, { 0,1 }, REWARD_H, REWARD_W, 0, 1, textures[BUBBLE], this, textures[REWARDS], OBJECT_REWARD);
		break;
	case 2:
		currReward = new ReviveButterflies(_pos, { 0,1 }, REWARD_H, REWARD_W, 0, 1, textures[BUBBLE], this, textures[REWARDS], OBJECT_REWARD);
		break;
	case 3:
		currReward = new BigBallons(_pos, { 0,1 }, REWARD_H, REWARD_W, 0, 1, textures[BUBBLE], this, textures[REWARDS], OBJECT_REWARD);
		break;
	default:
		break;
	}
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

//Carga el nivel(fondo,mariposas y flechas)
void Game::loadLevel() {
	cout << "Cargado el nivel : " << currLevel << endl;
	ballonScale = 1;
	background = new Background(WIN_HEIGHT, WIN_WIDTH, textures[LEVELS[currLevel].currTex]);
	currButterflies = LEVELS[currLevel].butterflyNum;
	cout << "Entran " << currButterflies << " mariposas." << endl;
	currArrows += LEVELS[currLevel].arrows; 
	cout << "Se recargan " << LEVELS[currLevel].arrows << " de flechas, total " << currArrows << endl;
	for (int i = 0; i < LEVELS[currLevel].butterflyNum; i++) {
		createButterfly();
	}
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
		deleteAllRewards();
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
void Game::deleteAllRewards() {
	cout << "Se borran todas las rewards que quedaron en la escena" << endl;
	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
		auto aux = dynamic_cast<Reward*>(*it);
		if (aux != nullptr && !aux->isDeleting()) {
			killObject(aux);
		}
	}
}
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
	cout << "Butterflies : " << currButterflies << endl;
	cout << "Arrows : " << currArrows << endl;
}

//Multiplica los puntos por cada globo que una flecha haya destruido y añade puntos extra
void Game::arrowStacks(int _stacks) {
	currPoints += pow(_stacks - 1, BONUS_POINTS) + POINTS_TO_ADD * _stacks;
	cout << "stacks! : " << _stacks << " // puntos = " << currPoints << " // Puntos agregados : " << _stacks * POINTS_TO_ADD << endl;
	SCB->updatePoints(currPoints);
}

//Comprueba el jugador a perdido el juego
void Game::endGame() {
	if (currButterflies == 0) {
		exit = true;
		cout << "Has matado todas las mariposas " << endl;
	}
	else if (arrows.empty() && currArrows == 0 && !bowCharged && eventObjects.size() <= 1) {
		exit = true;
		cout << "Te has quedado sin flechas" << endl;
	}
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

void Game::addButterflies(int _butterfliesToAdd) {
	currButterflies += _butterfliesToAdd;
	for (int i = 0; i < _butterfliesToAdd; i++) {
		createButterfly();
	}
}

void Game::saveGame(int partida){
	string filename = to_string(partida) + ".txt";
	ofstream sal (filename);
	string aux;
	//Primera línea para guardar todos los datos de game
	sal << "nivel " << currLevel << " points " << currPoints << " arrows " << currArrows << " butterflies " << currButterflies << " bScale " << ballonScale << " bowCharged " << bowCharged << endl;
	sal << gameObjects.size() << endl; //Segunda linea para saber el numero de objetos que hay
	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
		if (dynamic_cast<ArrowGameObject*>(*it) != nullptr) {
			dynamic_cast<ArrowGameObject*>(*it)->saveToFile(aux);
			sal << aux << endl;				//Cada objeto en una linea con TODOS sus datos
			aux = "";
		}
		else {
			sal << "ONG" << endl; //Objeto No Guardable (Pasa con el Scoreboard)
		}
	}
	sal.close();
	cout << "save game " << partida;
}