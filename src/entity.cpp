#include <Entity.hpp>

Entity::Entity(Posn p, Posn v, Posn dim, SDL_Texture* texture) 
	:pos(p), speed(v), dimensions(dim), tex(texture)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = dimensions.getX();
	currentFrame.h = dimensions.getY();
}

Entity::Entity(Posn p, Posn dim, SDL_Texture* texture) 
	:Entity(p, Posn(0.0f, 0.0f), dim, texture) {}

Posn& Entity::getPos() {
	return pos;
}

Posn& Entity::getSpeed() {
	return speed;
}

Posn& Entity::getDim() {
	return dimensions;
}

SDL_Rect Entity::getCurrentFrame() {
	return currentFrame;
}

SDL_Texture* Entity::getTex() {
	return tex;
}

void Entity::setPos(Posn p) {
	pos = p;
}

void Entity::setXPos(float x) {
	pos.setX(x);
}

void Entity::setYPos(float y) {
	pos.setY(y);
}

void Entity::setSpeed(Posn s) {
	speed = s;
}

void Entity::setXSpeed(float x) {
	speed.setX(x);
}

void Entity::setYSpeed(float y) {
	speed.setY(y);
}

void Entity::setTex(SDL_Texture* texture) {
	tex = texture;
}

void Entity::move() {
	pos = pos.addPosn(speed);
}
