#pragma once

class GameObject
{
public:
	GameObject() {};
	virtual ~GameObject() {};
	//M�todos genericos
	virtual void render() = 0;
	virtual void update() = 0;
};

