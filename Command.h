#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

#include "Entity.h"

class Command {
public:
	virtual void execute() = 0;
};

class Move: public Command {
public:
	Move(Player* player, Player::Direction direction);
	void execute();
private:
	Player* player;
    Player::Direction direction;
};



#endif // COMMAND_H_INCLUDED
