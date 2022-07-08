/*
 * Renderer.cpp
 *
 *  Created on: Jun 30, 2022
 *      Author: hector
 */

#include "Renderer.h"
#include <iostream>
#include <SDL2/SDL2_gfxPrimitives.h>

#define WINHEIGHT 720
#define WINWIDTH 720

std::unique_ptr<Renderer> Renderer::_instance;

Renderer::Renderer() {
	_window = SDL_CreateWindow("tic tac toe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINHEIGHT, WINWIDTH, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	_SDLrenderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

}

Renderer::~Renderer() {
	SDL_DestroyRenderer(_SDLrenderer);
	SDL_DestroyWindow(_window);
	std::cout << "deleting renderer" << std::endl;
}

SDL_Renderer* Renderer::getSDLRenderer() const {
	return _SDLrenderer;
}

SDL_Window* Renderer::getSDLWindow() const {
	return _window;
}

Renderer & Renderer::getInstance() {
	if (_instance == nullptr)
		_instance = std::make_unique<Renderer>();
	return *_instance;
}

void Renderer::drawCircle(int tile) const{
	int line = tile % 3;
	int column = tile / 3;

	int tileHeight = WINHEIGHT / 3;
	int tileWidth = WINWIDTH / 3;

	int XcenterTile = line * tileWidth + tileWidth / 2;
	int YcenterTile = column * tileHeight + tileHeight / 2;

	circleRGBA(_SDLrenderer, XcenterTile, YcenterTile, tileWidth / 4, 0, 255, 0, 255);
}

void Renderer::drawCross(int tile) const {
	SDL_SetRenderDrawColor(_SDLrenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

	int line = tile % 3;
	int column = tile / 3;

	int tileHeight = WINHEIGHT / 3;
	int tileWidth = WINWIDTH / 3;

	int XcenterTile = line * tileWidth + tileWidth / 2;
	int YcenterTile = column * tileHeight + tileHeight / 2;

	// draw first line
	SDL_RenderDrawLine(_SDLrenderer, XcenterTile - tileWidth/4, YcenterTile - tileHeight/4, XcenterTile + tileWidth/4, YcenterTile + tileHeight/4);

	// draw second line
	SDL_RenderDrawLine(_SDLrenderer, XcenterTile + tileWidth/4, YcenterTile - tileHeight/4, XcenterTile - tileWidth/4, YcenterTile + tileHeight/4);
}

void Renderer::drawGameBoard() const {
	SDL_SetRenderDrawColor(_SDLrenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

	int tileHeight = WINHEIGHT / 3;
	int tileWidth = WINWIDTH / 3;

	// draw vertical lines
	for (int i = 1; i < 3; ++i) {
		SDL_RenderDrawLine(_SDLrenderer, tileWidth *i, 0, tileWidth*i, WINHEIGHT);
	}

	// draw hirizontal lines
	for (int i = 1; i < 3; ++i) {
		SDL_RenderDrawLine(_SDLrenderer, 0, tileHeight*i, WINWIDTH, tileHeight*i);
	}

}

void Renderer::clear() const {
	SDL_SetRenderDrawColor(_SDLrenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(_SDLrenderer);
}

void Renderer::renderPresent() const {
	SDL_RenderPresent(_SDLrenderer);
}






