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
	Texture* texture = nullptr;		//Puntero a la tectura del objeto
	int idObject = 0;
	ArrowGameObject(Point2D _pos, Vector2D _dir,int _h, int _w,int _angle, int _scale, Texture* _texture, Game* _game,int _ID);
	ArrowGameObject() {};
public:
	//M�todos g�nericos
	virtual ~ArrowGameObject();
	virtual void render() const;			//La funci�n render es la misma para todos, creo que no deber�a ser virtual aqui (pero dentro de gameObject deber�a seguir siendo virtual)
	virtual void update() {};
	void loadFromFile() {};
	void saveToFile() {};
	SDL_Rect getRect() const;
};