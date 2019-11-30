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
	bubleTex = nullptr;
	rewardsTex = nullptr;
}

void Reward::handleEvent(const SDL_Event event) {
	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
		SDL_Point p = { event.button.x, event.button.y };
		SDL_Rect* r = new SDL_Rect();
		if (currState == INSIDE) {
			r->x = this->pos.getX();
			r->y = this->pos.getY();
			r->h = BUBBLE_Y_SIZE;
			r->w = BUBBLE_X_SIZE;
		}
		else if (currState == OUTSIDE) {
			r->x = REWARD_GAP_X + this->pos.getX();
			r->y = REWARD_GAP_Y + this->pos.getY();
			r->h = this->h;
			r->w = this->w;
		}
		if (SDL_PointInRect(&p, r) == SDL_TRUE) {
			if (currState == INSIDE) currState = OUTSIDE;
			else if (currState == OUTSIDE) {
				action();
				currState = PICKED;
			}
		}
		r = nullptr;
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

void Reward::saveToFile(string& data) {
	ArrowGameObject::saveToFile(data);
	data += " kind " + to_string(currRow);
}

void AddArrows::action() {
	game->addArrows(ARROWS_TO_ADD); 
};

void RemoveArrows::action() {
	game->addArrows(ARROWS_TO_REMOVE);
};

void ReviveButterflies::action() {
	game->addButterflies(BUTTERFLIES_TO_ADD);
};

void BigBallons::action() {
	game->setBallonScale(BALLON_BIG_SCALE);
};




