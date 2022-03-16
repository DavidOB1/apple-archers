#pragma once

#include <Entity.hpp>


class Apple : public Entity {
public:
	Apple(SDL_Texture* tex);
	int update();
	bool getHit();
	void setHit(bool b);
	void setAngle(double d);
private:
	bool hit;
	double oldAngle, newAngle;
};