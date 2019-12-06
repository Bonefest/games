#include "InputHandler.h"
#include "Game.h"

void InputHandler::onKeyPressed(EventKeyboard::KeyCode key) {
    keyManager.setKey(key);

    Entity* player = Game::getInstance()->getPlayer();
    player->getCurrentState()->onKeyPressed(player, key);
}

void InputHandler::onKeyReleased(EventKeyboard::KeyCode key) {
    keyManager.removeKey(key);


    Entity* player = Game::getInstance()->getPlayer();
    player->getCurrentState()->onKeyReleased(player, key);
}


