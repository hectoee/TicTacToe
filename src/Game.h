/*
 * Game.h
 *
 *  Created on: Jul 5, 2022
 *      Author: hector
 */

#include <vector>
#include <string>
#include "Player.h"

#ifndef GAME_H_
#define GAME_H_

class Game {
private:
	Player * _player1;
	Player * _player2;
	Player * _currentPlayer;
	bool _isFinished;

	std::string _endingStr;

	std::vector<std::vector<Player::Type>> _board;

private:
	void XYToLineCol(int xpos, int ypos, int * line, int * col);

	void switchPlayer();

	void checkWin();

	void checkDraw();

	void win();

	void draw();

public:
	Game();
	virtual ~Game();

	void drawBoard() const ;

	void playOneRound(int xMousPos, int yMousePos);

};

#endif /* GAME_H_ */
