/*
 * Player.cpp
 *
 *  Created on: Jul 5, 2022
 *      Author: hector
 */

#include "Player.h"

Player::Player(Type type)
: _type(type)
{
}

Player::~Player() {

}

Player::Type Player::getType() const {
	return _type;
}
