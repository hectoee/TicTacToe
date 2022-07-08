/*
 * Player.h
 *
 *  Created on: Jul 5, 2022
 *      Author: hector
 */

#ifndef PLAYER_H_
#define PLAYER_H_

class Player {
protected:
	enum Type {
		Nothing,
		Cross,
		Circle
	};
	friend class Game;

private:
	Type _type;

public:
	Player(Type type = Cross);
	virtual ~Player();

	Type getType() const;
};

#endif /* PLAYER_H_ */
