#include "Reward.h"
#include "Game.h"


Reward::Reward(Point2D _pos, Vector2D _dir, int _h, int _w, int _angle, int _scale, Texture* _bubleTex, Texture* reward_tex, Game* _game, int _id)
	:ArrowGameObject(_pos, _dir, _h, _w, _angle, _scale, _bubleTex, _game, _id)
{
	bubleTex = _bubleTex;
	rewardsTex = reward_tex;
	collisionable = true;
}

Reward::~Reward() {

}

void Reward::handleEvent(const SDL_Event event) {
	if (currState == INSIDE && event.type == SDL_MOUSEBUTTONDOWN) {
		currState = OUTSIDE;
	}
	else if (currState == OUTSIDE && event.type == SDL_MOUSEBUTTONDOWN) {
		action();
		currState = PICKED;
	}
}

void Reward::update() {
	pos.setY(pos.getY() + dir.getY() * MAX_SPEED_REW);
	currCol++;
	if (currCol >= MAX_COLS) currCol = 0;
	if (pos.getY() > MAX_Y_POS || currState == PICKED) {
		game->killObject(this);
	}
}

void Reward::render() const {
	rewardsTex->renderFrame({ pos.getX() + REWARD_GAP_X,pos.getY() + REWARD_GAP_Y,w,h }, currRow, currCol, angle, SDL_FLIP_NONE);
	if (currState == INSIDE) {
		bubleTex->render({ pos.getX(),pos.getY(),BUBBLE_Y_SIZE,BUBBLE_X_SIZE }, SDL_FLIP_NONE);
	}
}

void AddArrows::action() {
	game->addArrows(ARROWS_TO_ADD); 
};

