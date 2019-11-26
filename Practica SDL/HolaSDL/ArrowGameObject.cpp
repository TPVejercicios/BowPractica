#include "ArrowGameObject.h"
#include <iostream>
using namespace std;

ArrowGameObject::ArrowGameObject(Point2D _pos, Vector2D _dir, int _h, int _w, int _angle, int _scale, Texture* _texture, Game* _game,int _id){
	pos = _pos;
	dir = _dir;
	h = _h;
	w = _w;
	angle = _angle;
	scale = _scale;
	texture = _texture;
	game = _game;
	objectID = _id;
}

ArrowGameObject::~ArrowGameObject() {
	texture = nullptr;
	game = nullptr;
}

void ArrowGameObject::loadFromFile() {
	cout << "Objeto cargado" << endl;

}

void ArrowGameObject::saveToFile(string &data) {
	data = "ObjetoArrowGameObject guardado";
	//data = "posx " + pos.getX() + " posy " + pos.getY() + " dirx " + dir.getX() + " diry " + dir.getY() + " h " + h;	//Aqui todos los datos que ya pose� ArrowGameObject
}
