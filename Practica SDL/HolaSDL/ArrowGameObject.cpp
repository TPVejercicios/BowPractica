#include "ArrowGameObject.h"
#include <iostream>
#include <string>
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

//Información para guardar que comparte cada ArrowGameObject
void ArrowGameObject::saveToFile(string& data) {
	data = "id " + to_string(objectID) + " posx " + to_string(pos.getX()) + " posy " + to_string(pos.getY()) + " dirx " + to_string(dir.getX()) 
		+ " diry " + to_string(dir.getY()) + " h " + to_string(h) + " w " + to_string(w) + " angle " + to_string(angle)
		+ " scale " + to_string(scale) + " collisionable " + to_string(collisionable) + " deleting " + to_string(deleting);
}
