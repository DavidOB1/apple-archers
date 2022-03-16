#include <Arrow.hpp>
#include <math.h>

int mX;
int mY;
int inverser;
bool offScreen;
Posn arCenter;
Posn arPoint;
Posn apCenter;


Arrow::Arrow(Posn startingPos, SDL_Texture* tex)
	:Entity(startingPos, Posn(72, 17), tex)
{
	SDL_GetMouseState(&mX, &mY);
	if (mX - getPos().getX() == 0) {
		inverser = (mY - getPos().getY() > 0) ? 1 : -1;
		angle = 1.5707965 * inverser;
	}
	else
		angle = atan((mY - getPos().getY()) / (mX - getPos().getX())); // in radians

	inverser = (mX - getPos().getX() > 0) ? 1 : -1;
	setXSpeed(inverser * 15 * cos(angle));
	setYSpeed(inverser * 15 * sin(angle));
}

double Arrow::getAngle() {
	return angle;
}

bool Arrow::update() {

	offScreen = (getPos().getY() > 591) || (getPos().getX() < -100) || (getPos().getX() > 1380);

	move();

	if (getSpeed().getX() == 0) {
		inverser = (getSpeed().getY() > 0) ? 1 : -1;
		angle = 1.5707965 * inverser;
	}
	else if (getSpeed().getX() < 0)
		angle = 3.14159265 + atan(getSpeed().getY() / getSpeed().getX());
	else
		angle = atan(getSpeed().getY() / getSpeed().getX());
	

	setYSpeed(getSpeed().getY() + 0.15);

	return offScreen;
}

bool Arrow::hitApple(Apple a) {

	arCenter = getPos().addPosn(Posn(36, 8.5));
	apCenter = a.getPos().addPosn(Posn(16, 16));

	for (int i = -1; i != 2; ++i) {
		arPoint = arCenter.addPosn(Posn(i * 36 * (cos(angle)), i * 36 * sin(angle)));
		if (arPoint.distanceTo(apCenter) < 17)
			return true;
	}

	return false;
}