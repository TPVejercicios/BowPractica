#pragma once

using namespace std;

class Vector2D {
private:
	int X = 0;
	int Y = 0;

public:
	Vector2D() {};
	Vector2D(int x, int y) { X = x; Y = y; };

	int getX() const { return X; };
	int getY() const { return Y; };
	void setX(int valor) { X = valor; };
	void setY(int valor) { Y = valor; };
	void subVectorInY(Vector2D vel) { Y -= vel.Y; };
};

