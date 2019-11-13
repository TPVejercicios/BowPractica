#include "Vector2D.h"
#include <math.h>


void Vector2D::normalize() {
	double mag = sqrt(pow(X, 2) + pow(Y, 2));
	if (mag > 0.0) {
		X = X / mag;
		Y = Y / mag;
	}
}

Vector2D Vector2D::operator+(const Vector2D& v) const {
	Vector2D r;
	r.X = this->X + v.X;
	r.Y = this->Y + v.Y;
	return r;
}

Vector2D Vector2D::operator*(double d) const {
	Vector2D r;
	r.X = X * d;
	r.X = Y * d;
	return r;
}
double Vector2D::operator*(const Vector2D& d) const {
	return d.X * X + d.Y * Y;
}
