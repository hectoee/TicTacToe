/*
 * Renderer.h
 *
 *  Created on: Jun 30, 2022
 *      Author: hector
 */

#include <SDL2/SDL.h>
#include <memory>
#include "Player.h"

#ifndef RENDERER_H_
#define RENDERER_H_

class Renderer {
private:
	SDL_Renderer * _SDLrenderer;
	static std::unique_ptr<Renderer> _instance;

	SDL_Window * _window;

public:
	Renderer();
	virtual ~Renderer();

	Renderer & operator=(Renderer &) = delete;

	void drawCircle(int tile) const;

	void drawCross(int tile) const;

	void drawGameBoard() const;

	SDL_Renderer * getSDLRenderer() const;

	SDL_Window * getSDLWindow() const;

	static Renderer & getInstance();

	void clear() const;

	void renderPresent() const;
};

#endif /* RENDERER_H_ */
