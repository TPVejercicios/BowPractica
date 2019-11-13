#pragma once

using namespace std;
//using Point2D = Vector2D;

class Vector2D {
private:
	double X = 0;
	double Y = 0;

public:
	Vector2D() {};
	Vector2D(int x, int y) { X = x; Y = y; };

	double getX() const { return X; };
	double getY() const { return Y; };
	void setX(int valor) { X = valor; };
	void setY(int valor) { Y = valor; };
	void subVectorInY(Vector2D vel) { Y -= vel.Y; };
	void multiply(int n) { X* n; Y* n; };
	void normalize();
	Vector2D operator+(const Vector2D& v) const;
	Vector2D operator*(double d) const;
	double operator*(const Vector2D& d) const;

};
