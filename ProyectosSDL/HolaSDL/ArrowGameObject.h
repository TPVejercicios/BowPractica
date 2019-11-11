#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include "Texture.h"

using Point2D = Vector2D;

class ArrowGameObject : public GameObject
{
private:
protected:
	Point2D pos;
	Vector2D angle;
	Vector2D scale;
	Game* game = nullptr;
	Texture* texture = nullptr;
	//vector<Texture*> textures; Si tenemos aqui un vector de texturas podremos tener las 2 texturas del arco por ejemplo para cambiar entre ellas
	SDL_Rect* body = nullptr;
	ArrowGameObject(Point2D _pos, Vector2D _angle, Vector2D _scale, Game* _game, Texture* _texture, SDL_Rect* _body);
	ArrowGameObject() {};
public:
	
	virtual ~ArrowGameObject();
	virtual void render() const ;
	virtual void update();
	virtual SDL_Rect* getDestRect() { return body; };
	virtual SDL_Rect* getCollisionRect() { return body; };
	void loadFromFile() {};
	void saveToFile() {};
};

