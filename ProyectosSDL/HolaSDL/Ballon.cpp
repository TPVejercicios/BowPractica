#include "Ballon.h"

using namespace std;



Ballon::Ballon(Texture* ballonSprite, Game* _game)
	:ArrowGameObject(_game)
{
	texture = ballonSprite;
	int seed = rand() % 100;
	srand(seed);
	pos.setX((rand() % (WIN_WIDTH / 2)) + (WIN_WIDTH / 2) - 50);
	pos.setY(WIN_HEIGHT);
	dir.setX(0);
	dir.setY((rand() % (MAX_BALLON_SPEED + 1)) + 3);
	numTexture = rand() % (texture->getNumCols() + 1);
	scale = 40;
	body->h = texture->getH() / scale;
	body->w = texture->getW() / 30;
	body->x = pos.getX() + gap;
	body->y = pos.getY() + gap;
	collisionBody = body;
}

//Destructora de Ballon
Ballon::~Ballon() {
	try {
		texture = nullptr;
		cout << "Se ha eliminado un globo " << endl;
	}
	catch (exception e) {
		cout << "Error deleting ballon" << e.what() << endl;
	}
}

//Renderiza el globo
void Ballon::render() const {
	texture->renderFrame(*body, numTexture,collFrame,1,SDL_FLIP_NONE);
}

//Mueve el globo en función de su velocidad
//Segund implementación meter el objecto a una lista de objectos a borrar
void Ballon::update() {
	if (status == SWOLLEN) {
		body->x = pos.getX() + gap;
		body->y = pos.getY() + gap;
		pos.subVectorInY(dir);

		//game->checkCrushBallon();
		if (pos.getY() < -100) {//Si el ballon sale por arriba con un extra de 100 para que se vea como sale de escena
			//Aqui llamar a killObject();
		}
	}
	else
	{
		collFrame++;
		if (collFrame > texture->getNumCols()) {
			//killObject();
		}
	}
}
