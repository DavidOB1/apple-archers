#pragma once

#include <Entity.hpp>


class Player : public Entity {
public:
	Player(Posn startingPos, SDL_Texture* tex1, SDL_Texture* tex2);
	void jump();
	void moveLeft();
	void moveRight();
	void update();
	bool getInAir();
private:
	bool inAir;
	SDL_Texture* leftTex;
	SDL_Texture* rightTex;
};