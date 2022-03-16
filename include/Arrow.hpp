#pragma once

#include <Entity.hpp>
#include <Apple.hpp>


class Arrow : public Entity {
public:
	Arrow(Posn startingPos, SDL_Texture* tex);
	double getAngle();
	bool update();
	bool hitApple(Apple a);
private:
	double angle;
};