#pragma once
#include "EventHandler.h"
#include "ArrowGameObject.h"
/*Modela a los premios del juego y hereda de ArrowsGameObject y de EventHandler.
(Re)dene por tanto los metodos update, render y handleEvent. A~nade al menos un nuevo atributo
para el estado del premio (si esta dentro de una burbuja o no). Se daran detalles en clase sobre la forma
de gestionar los distintos tipos de premios y sus acciones asociadas.*/
enum state
{
	INSIDE, OUTSIDE
};
class Reward: public ArrowGameObject, public EventHandler
{
private:
	state currState = INSIDE;
protected:
public:
	virtual void render() const {};
	virtual void update() {};
	virtual void handleEvent(const SDL_Event _event) {};
};

