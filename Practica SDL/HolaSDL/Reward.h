#pragma once
#include "EventHandler.h"
#include "ArrowGameObject.h"
/*Modela a los premios del juego y hereda de ArrowsGameObject y de EventHandler.
(Re)dene por tanto los metodos update, render y handleEvent. A~nade al menos un nuevo atributo
para el estado del premio (si esta dentro de una burbuja o no). Se daran detalles en clase sobre la forma
de gestionar los distintos tipos de premios y sus acciones asociadas.*/

class Game;

const int MAX_COLS = 8;
const int MAX_FILS = 10;
const int MAX_Y_POS = 700;
const int MAX_SPEED_REW = 5;
const int ARROWS_TO_ADD = 5;
const int BUBBLE_X_SIZE = 90;
const int BUBBLE_Y_SIZE = 90;
const int REWARD_GAP_X = 20;
const int REWARD_GAP_Y = 30;

enum state_reward
{
	INSIDE, OUTSIDE, PICKED
};
class Reward: public ArrowGameObject, public EventHandler
{
private:
	state_reward currState = INSIDE;
	Texture* bubleTex = nullptr;
	Texture* rewardsTex = nullptr;
	int currCol = 0;
	int currRow = 0;

protected:
public:
	Reward(Point2D _pos, Vector2D _dir, int _h, int _w, int _angle, int _scale, Texture* _bubleTex,Texture* reward_tex, Game* _game,int _id);
	~Reward();
	virtual void render() const;
	virtual void update();
	virtual void handleEvent(const SDL_Event event);
	virtual void action() = 0;
};

class AddArrows : public Reward
{
public:
	AddArrows::AddArrows(Point2D _pos, Vector2D _dir, int _h, int _w, int _angle, int _scale, Texture* _bubleTex, Game* _game, Texture* _currTex, int _id)
		: Reward(_pos, _dir, _h, _w, _angle, _scale, _bubleTex, _currTex, _game, _id) {};
	virtual void action();
};

