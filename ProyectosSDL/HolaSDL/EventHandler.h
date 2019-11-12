#pragma once
#include "GameObject.h"
#include "SDL.h"

class EventHandler : public GameObject
{
protected:
	EventHandler() {};

public:
	~EventHandler() {};
	virtual void render() const = 0;
	virtual void update() = 0;
	//
	virtual void handleEvent(const SDL_Event event) = 0;
};

