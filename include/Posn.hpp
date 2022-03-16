#pragma once


class Posn {
public:
	Posn();
	Posn(float x, float y);
	float getX();
	float getY();
	void setX(float x);
	void setY(float y);
	Posn addPosn(Posn p);
	double distanceTo(Posn p);
	void print();
private:
	float x, y;
};