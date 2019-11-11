#pragma once
#include "ArrowGameObject.h"

class GameObject
{
public:
	GameObject() {};
	virtual ~GameObject() {};
	//Métodos genericos
	virtual void render() const = 0;
	virtual void update() = 0;
};

