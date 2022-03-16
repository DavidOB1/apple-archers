#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <Entity.hpp>
#include <Arrow.hpp>


class RenderWindow {
public:
	RenderWindow(const char* title, int w, int h);
	SDL_Texture* loadTexture(const char* filePath);
	void clear();
	void render(Entity& entity);
	void renderArrow(Arrow& arrow);
	void display();
	void cleanUp();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};