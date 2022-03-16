#include <Posn.hpp>

#include <iostream>
#include <math.h>
#include <cmath>


Posn::Posn(float x, float y) {
	this->x = x;
	this->y = y;
}

Posn::Posn() {
	x = 0.0f;
	y = 0.0f;
}

float Posn::getX() {
	return x;
}

float Posn::getY() {
	return y;
}

void Posn::setX(float x) {
	this->x = x;
}

void Posn::setY(float y) {
	this->y = y;
}

Posn Posn::addPosn(Posn p) {
	return Posn(x + p.getX(), y + p.getY());
}

double Posn::distanceTo(Posn p) {
	return sqrt(pow(x - p.getX(), 2) + pow(y - p.getY(), 2));
}

void Posn::print() {
	std::cout << x << ", " << y << std::endl;
}