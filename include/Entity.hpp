#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <Posn.hpp>


class Entity {
public:
	Entity(Posn p, Posn v, Posn dimensions, SDL_Texture* texture);
	Entity(Posn p, Posn dim, SDL_Texture* texture);
	Entity() = default;
	Posn& getPos();
	Posn& getSpeed();
	Posn& getDim();
	SDL_Rect getCurrentFrame();
	SDL_Texture* getTex();
	void setPos(Posn p);
	void setXPos(float x);
	void setYPos(float y);
	void setSpeed(Posn s);
	void setXSpeed(float x);
	void setYSpeed(float y);
	void setTex(SDL_Texture* texture);
	void move();
private:
	Posn pos, speed, dimensions;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};