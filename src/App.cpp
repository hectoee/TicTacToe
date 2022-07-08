/*
 * App.cpp
 *
 *  Created on: Jun 30, 2022
 *      Author: hector
 */

#include <iostream>
#include <SDL2/SDL_ttf.h>
#include "App.h"
#include "Renderer.h"

App::App()
: _running(true)
{
	_game = std::make_unique<Game>();
}

App::~App() {
}

int App::onExecute() {
	if(onInit() == false) {
	       return -1;
	 }

	 SDL_Event Event;


	 while(_running) {
	     while(SDL_PollEvent(&Event)) {
	        onEvent(&Event);
	     }

	     onLoop();

	     onRender();

	 }


	 onCleanup();

	 return 0;
}

bool App::onInit() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0 ){
	return false;
	}

	if (TTF_Init() < 0) {
		return false;
	}

	Renderer & renderer = Renderer::getInstance();

	if (renderer.getSDLWindow() == NULL)
		return false;
	if (renderer.getSDLRenderer() == NULL)
		return false;

	std::cout << "starting..." << std::endl;

	return true;
}

void App::onEvent(SDL_Event* event) {
	switch (event->type) {
	case SDL_QUIT :
		exit();
		break;
	case SDL_KEYDOWN:
		std::cout << (char) event->key.keysym.sym << std::endl;
		if (event->key.keysym.sym == 'q')
			exit();
		break;
	case SDL_MOUSEBUTTONDOWN:
		std::cout << "press" << std::endl;
		if (event->button.button == SDL_BUTTON_LEFT)
			_game->playOneRound(event->button.x, event->button.y);
		break;
	default:
		break;
	}
}

void App::onLoop() {

}

void App::onRender() {
	Renderer & renderer = Renderer::getInstance();
	renderer.clear();

	_game->drawBoard();

	renderer.renderPresent();
}

void App::onCleanup() {
	SDL_Quit();
	std::cout << "cleanup app" <<std::endl;
}

void App::exit() {
	std::cout << "exiting..." << std::endl;
	_running = false;
}

