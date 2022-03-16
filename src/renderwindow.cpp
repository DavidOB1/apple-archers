#include <RenderWindow.hpp>
#include <iostream>


RenderWindow::RenderWindow(const char* title, int w, int h)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);

	if (window == NULL)
		std::cout << "WINDOW INIT ERROR: " << SDL_GetError() << std::endl;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

SDL_Texture* RenderWindow::loadTexture(const char* filePath) {
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, filePath);

	if (texture == NULL)
		std::cout << "TEXTURE ERROR: " << SDL_GetError() << std::endl;

	return texture;
}

void RenderWindow::clear() {
	SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& entity) {
	SDL_Rect src;
	src.x = entity.getCurrentFrame().x;
	src.y = entity.getCurrentFrame().y;
	src.w = entity.getCurrentFrame().w;
	src.h = entity.getCurrentFrame().h;

	SDL_Rect dst;
	dst.x = entity.getPos().getX();
	dst.y = entity.getPos().getY();
	dst.w = entity.getCurrentFrame().w;
	dst.h = entity.getCurrentFrame().h;

	SDL_RenderCopy(renderer, entity.getTex(), &src, &dst);
}

void RenderWindow::renderArrow(Arrow& arrow) {
	SDL_Rect src;
	src.x = arrow.getCurrentFrame().x;
	src.y = arrow.getCurrentFrame().y;
	src.w = arrow.getCurrentFrame().w;
	src.h = arrow.getCurrentFrame().h;

	SDL_Rect dst;
	dst.x = arrow.getPos().getX();
	dst.y = arrow.getPos().getY();
	dst.w = arrow.getCurrentFrame().w;
	dst.h = arrow.getCurrentFrame().h;

	SDL_RenderCopyEx(renderer, arrow.getTex(), &src, &dst, 57.2957795 * arrow.getAngle(), NULL, SDL_FLIP_NONE);
}

void RenderWindow::display() {
	SDL_RenderPresent(renderer);
}

void RenderWindow::cleanUp() {
	SDL_DestroyWindow(window);
}