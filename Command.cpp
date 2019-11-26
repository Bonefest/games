#include "Command.h"

Move::Move(Player* player, Player::Direction direction) {
    this->player = player;
    this->direction = direction;
}

void Move::execute() {
    player->setDirection(direction);
}
