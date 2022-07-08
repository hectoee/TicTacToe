/*
 * App.h
 *
 *  Created on: Jun 30, 2022
 *      Author: hector
 */

#include <SDL2/SDL.h>
#include <memory>
#include "Game.h"

#ifndef APP_H_
#define APP_H_

class App {
private:
	bool _running;
	std::unique_ptr<Game> _game;

public:
	App();
	virtual ~App();

	int onExecute();

	bool onInit();

	void onEvent(SDL_Event* event);

	void onLoop();

	void onRender();

	void onCleanup();

	void exit();

};

#endif /* APP_H_ */
