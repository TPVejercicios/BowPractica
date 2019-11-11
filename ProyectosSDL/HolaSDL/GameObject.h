#pragma once
#include "Game.h"


class GameObject
{
public:
	GameObject() {};
	virtual ~GameObject() {};
	//M�todos genericos
	virtual void render() const = 0;
	virtual void update() = 0;
};

