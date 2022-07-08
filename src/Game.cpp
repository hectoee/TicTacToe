/*
 * Game.cpp
 *
 *  Created on: Jul 5, 2022
 *      Author: hector
 */

#include "Game.h"
#include "Renderer.h"
#include <iostream>
#include <SDL2/SDL_ttf.h>
#include <cassert>

Game::Game()
: _player1(new Player(Player::Cross)), _player2(new Player(Player::Circle)), _currentPlayer(_player1), _isFinished(false), _endingStr("")
{
	_board = { { Player::Nothing, Player::Nothing, Player::Nothing },
			   { Player::Nothing, Player::Nothing, Player::Nothing },
			   { Player::Nothing, Player::Nothing, Player::Nothing },
			 };
}

Game::~Game() {
	delete _player1;
	delete _player2;
	std::cout << "deleting game" << std::endl;
}

void Game::switchPlayer() {
	if (_currentPlayer == _player1)
		_currentPlayer = _player2;
	else
		_currentPlayer = _player1;
}

void Game::drawBoard() const {
	Renderer & rend = Renderer::getInstance();
	rend.drawGameBoard();

	int index = 0;
	for (std::vector<Player::Type> vec : _board) {
		for (Player::Type type : vec) {
			if (type == Player::Cross)
				rend.drawCross(index);
			else if (type == Player::Circle)
				rend.drawCircle(index);
			++ index;
		}
	}
}

void Game::XYToLineCol(int xpos, int ypos, int * line, int * col) {
	int tileSize= 720 / 3;

	*line = ypos / tileSize;
	*col = xpos / tileSize;
}

void Game::playOneRound(int x, int y) {
	if (_isFinished) return;

	int line, col;
	XYToLineCol(x, y, &line, &col);
	if (line < 0 || line > 2 || col < 0 || col > 2) return ;

	if (_board[line][col] == Player::Nothing) {
		_board[line][col] = _currentPlayer->getType();
		checkWin();
		checkDraw();
		switchPlayer();
	}
}

void Game::checkWin() {
	Player::Type goodType = _currentPlayer->getType();
	// check lines
	for (auto it = _board.begin(); it != _board.end(); ++ it) {
		int sum = 0;
		for (auto it2 = (*it).begin(); it2 != (*it).end(); ++it2) {
			if (*it2 != goodType) break;
			else ++ sum;
		}
		if (sum == 3){
			win();
			return;
		}
		sum = 0;
	}

	// check columns
	for (int j = 0; j < 3; j++) {
		int sum = 0;
		for (int i = 0; i < 3; i ++) {
			if (_board[i][j] != goodType) break;
			else ++ sum;
		}
		if (sum == 3){
			win();
			return;
		}
		sum = 0;
	}

	// check diagnonales
	int sum = 0;
	for (int i = 0; i < 3; i++) {
		if (_board[i][i] != goodType) break;
		else sum ++;
	}
	if (sum == 3) {
		win();
		return;
	}

	sum = 0;
	for (int i = 0; i < 3; i ++) {
		if (_board[i][2-i] != goodType) break;
		else sum ++;
	}
	if (sum == 3) {
		win();
		return;
	}


}

void Game::checkDraw() {
	for (auto it = _board.begin(); it != _board.end(); ++ it) {
		for (auto it2 = (*it).begin(); it2 != (*it).end(); ++it2) {
			if (*it2 == Player::Nothing) return;
		}
	}
	draw();
}

void Game::win() {
	_isFinished = true;
	std::string winningPlayer = (_currentPlayer == _player1) ? "Cross" : "Circle";
	_endingStr =  winningPlayer + " won !" ;
	std::cout << _endingStr << std::endl;
}

void Game::draw() {
	_isFinished = true;
	_endingStr = "Draw...";
	std::cout << _endingStr << std::endl;
}

