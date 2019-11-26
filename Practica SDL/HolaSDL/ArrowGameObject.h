#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include "Texture.h"

class Game;
using Point2D = Vector2D;

//ArrowGameObject hereda de GameObject
class ArrowGameObject : public GameObject{
private:
protected:
	Point2D pos;					//Posicion del objeto
	Vector2D dir;					//Direccion del objeto
	int h = 0, w = 0;				//Tama�o del objeto
	int angle = 0;					//�ngulo del objeto
	int scale = 1;					//Escala del objeto
	Game* game = nullptr;			//Puntero a juego
	Texture* texture = nullptr;		//Puntero a la textura del objeto
	int objectID = 0;				//ID �nico del objeto
	bool collisionable = true;		//Para determinar si se puede collisionar contra �l
	bool deleting = false;			//Para determinar si est� en proceso de eliminaci�n 
	ArrowGameObject(Point2D _pos, Vector2D _dir,int _h, int _w,int _angle, int _scale, Texture* _texture, Game* _game,int _id);
	ArrowGameObject() {};
public:
	//M�todos g�nericos
	virtual ~ArrowGameObject();
	virtual void render() const { texture->render(getRect(), SDL_FLIP_NONE); };		
	virtual void update() {};
	virtual int& getID() { return objectID; };
	virtual void startDestruction() {};
	virtual void loadFromFile();
	virtual void saveToFile(string &data);

	SDL_Rect getRect() const { return { pos.getX(),pos.getY(),w * scale,h * scale }; };
	bool isCollisionable() { return collisionable; };
	bool isDeleting() { return deleting; };
};