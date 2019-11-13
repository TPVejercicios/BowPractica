#pragma once

class GameObject
{
public:
	GameObject() {};
	virtual ~GameObject() {};
	//Métodos genericos
	virtual void render() = 0;
	virtual void update() = 0;
};

