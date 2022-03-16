#include <Apple.hpp>
#include <ctime>
#include <math.h>

int appleOffScreen;
int aInverser;


Apple::Apple(SDL_Texture* tex)
	:Entity(Posn(0, -50), Posn(0, 5), Posn(32, 32), tex)
{
	setXPos(200 + std::rand() / ((RAND_MAX + 1u) / 880));
	hit = false;
	oldAngle = 0.0;
	newAngle = 0.0;
}

int Apple::update() {

	if (getPos().getY() > 576)
		appleOffScreen = 1;
	else if ((getPos().getX() < -32) || (getPos().getX() > 1312))
		appleOffScreen = 2;
	else
		appleOffScreen = 0;

	move();

	if (hit) {

		if (getSpeed().getX() == 0) {
			aInverser = (getSpeed().getY() > 0) ? 1 : -1;
			setAngle(1.5707965 * aInverser);
		}
		else if (getSpeed().getX() < 0)
			setAngle(3.14159265 + atan(getSpeed().getY() / getSpeed().getX()));
		else
			setAngle(atan(getSpeed().getY() / getSpeed().getX()));

		setPos(getPos().addPosn(Posn(36 * (cos(newAngle) - cos(oldAngle)), 36 * (sin(newAngle) - sin(oldAngle)))));

		setYSpeed(getSpeed().getY() + 0.15);
	}

	return appleOffScreen;

}

bool Apple::getHit() {
	return hit;
}


void Apple::setHit(bool b) {
	hit = b;
}

void Apple::setAngle(double d) {
	oldAngle = newAngle;
	newAngle = d;
}