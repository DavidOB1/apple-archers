#include <Player.hpp>
#include <algorithm>

const float ground = 507.0f;
float xSpeed;
float ySpeed;
int mouseX;
int mouseY;


Player::Player(Posn startingPos, SDL_Texture* tex1, SDL_Texture* tex2)
	:Entity(startingPos, Posn(70, 101), tex1)
{
	inAir = (getPos().getY() < ground);
	leftTex = tex1;
	rightTex = tex2;
}

void Player::jump() {
	if (!inAir) {
		setYSpeed(-23);
		inAir = true;
	}
}

void Player::moveLeft() {
	setXSpeed(-8);
}

void Player::moveRight() {
	setXSpeed(8);
}

void Player::update() {
	
	move();

	if (getPos().getX() < 0)
		setXPos(0);
	else if (getPos().getX() > 1210)
		setXPos(1210);

	if (getPos().getY() > ground) {
		setYPos(ground);
		setYSpeed(0);
		inAir = false;
	}

	xSpeed = getSpeed().getX();
	ySpeed = getSpeed().getY();

	if (xSpeed < 0)
		setXSpeed(std::min(0.0, xSpeed + 1.2));
	else if (xSpeed > 0)
		setXSpeed(std::max(0.0, xSpeed - 1.2));

	if (inAir)
		setYSpeed(ySpeed + 1.5);

	SDL_GetMouseState(&mouseX, &mouseY);

	if (mouseX - 35 > getPos().getX())
		setTex(rightTex);
	else
		setTex(leftTex);
}

bool Player::getInAir() {
	return inAir;
}