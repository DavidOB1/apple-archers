#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <math.h>
#include <ctime>

#include <RenderWindow.hpp>
#include <Entity.hpp>
#include <Posn.hpp>
#include <Player.hpp>
#include <Arrow.hpp>
#include <Apple.hpp>

RenderWindow window = RenderWindow("Apple Archers", 1280, 720);
bool running = true;
bool startScreen = true;
SDL_Event event;
Entity bgObj;
Entity aaLogo;
Entity enterLogo;
std::vector<Arrow> arrows;
std::vector<Apple> apples;
int score = 0;
int appleStatus;
Uint64 currentTime;

SDL_Texture* bgTexture = window.loadTexture("res/green-background.png");
SDL_Texture* grassTex = window.loadTexture("res/grass-tile.png");
SDL_Texture* logoTexture = window.loadTexture("res/apple-archers-logo.png");
SDL_Texture* pressEnter = window.loadTexture("res/press-enter.png");
SDL_Texture* bowTexLeft = window.loadTexture("res/bow-guy-left.png");
SDL_Texture* bowTexRight = window.loadTexture("res/bow-guy-right.png");
SDL_Texture* arrowTexture = window.loadTexture("res/arrow.png");
SDL_Texture* appleTexture = window.loadTexture("res/apple.png");

Player guy = Player(Posn(640, 360), bowTexLeft, bowTexRight);


void drawBackground() {

	bgObj = Entity(Posn(0, 0), Posn(1280, 720), bgTexture);
	window.render(bgObj);

	for (int i = 0; i < 10; ++i) {
		bgObj = Entity(Posn(128 * i, 592), Posn(128, 128), grassTex);
		window.render(bgObj);
	}
}


void titleScreen() {

	currentTime = SDL_GetPerformanceCounter();

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT)
			running = false;

		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_RETURN)
				startScreen = false;
		}
	}

	window.clear();

	drawBackground();

	aaLogo = Entity(Posn(338.5, 232 + 20 * sin(currentTime * 0.0000002)), Posn(603, 68), logoTexture);
	enterLogo = Entity(Posn(546, 285 + 20 * sin(currentTime * 0.0000002)), Posn(188, 58), pressEnter);
	window.render(aaLogo);
	window.render(enterLogo);

	window.display();
}


void playGame() {

	currentTime = SDL_GetPerformanceCounter();
	
	const Uint8* keyState = SDL_GetKeyboardState(NULL);

	if (keyState[SDL_SCANCODE_A]) 
		guy.moveLeft();
	if (keyState[SDL_SCANCODE_D])
		guy.moveRight();
	if (keyState[SDL_SCANCODE_W] || keyState[SDL_SCANCODE_SPACE])
		guy.jump();

	guy.update();

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT)
			running = false;
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (event.button.button == SDL_BUTTON_LEFT)
				arrows.push_back(Arrow(guy.getPos().addPosn(Posn(35, 50.5)), arrowTexture));
		}
	}

	if (std::rand() / ((RAND_MAX + 1u) / 30) == 2)
		apples.push_back(Apple(appleTexture));

	window.clear();
	drawBackground();
	window.render(guy);

	for (unsigned i = 0; i < arrows.size(); ++i) {
		if (arrows[i].update())
			arrows.erase(arrows.begin() + i);
		else
			window.renderArrow(arrows[i]);
	}

	for (unsigned i = 0; i < apples.size(); ++i) {
		appleStatus = apples[i].update();
		if (appleStatus > 0) {
			apples.erase(apples.begin() + i);
			if (appleStatus == 2)
				score++;
		}
		else
			window.render(apples[i]);
	}

	for (Arrow& ar : arrows)
		for (Apple& ap : apples)
			if (ar.hitApple(ap) && !ap.getHit()) {
				ap.setSpeed(ar.getSpeed());
				ap.setAngle(ar.getAngle());
				ap.setHit(true);
			}

	window.display();
}

int main(int argc, char* args[]) {

	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "SDL_INIT ERROR: " << SDL_GetError() << std::endl;
	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_INIT ERROR: " << SDL_GetError() << std::endl;

	while (running) {
		if (startScreen)
			titleScreen();
		else
			playGame();
	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}