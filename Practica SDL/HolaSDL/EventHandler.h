#pragma once
#include "SDL.h"

class EventHandler
{
public:
	EventHandler() {};
	virtual ~EventHandler() {};
	virtual void handleEvents(const SDL_Event event) = 0;
};

