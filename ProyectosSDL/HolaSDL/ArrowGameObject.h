#pragma once

#include "Vector2D.h"
#include "GameObject.h"
#include "SDL.h"

class Game;

using Point2D = Vector2D;

//ArrowGameObject hereda de GameObject
class ArrowGameObject : public GameObject{
private:
protected:
	Point2D pos;
	Vector2D angle;
	Vector2D dir;
	int scale = 0;
	Game* game = nullptr;
	//Texture* texture = nullptr;
	SDL_Rect* body = nullptr; //sobra
	SDL_Rect* collisionBody = nullptr;
	ArrowGameObject(Game* _game);
	ArrowGameObject() {};
public:
	virtual ~ArrowGameObject();
	virtual void render() const {};
	virtual void update() {};
	//Métodos en común con todos los hijos
	virtual SDL_Rect* getDestRect() { return body; };
	virtual SDL_Rect* getCollisionRect() { return collisionBody; };
	virtual void loadFromFile() {};
	virtual void saveToFile() {};
};

