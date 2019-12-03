#include "InputHandler.h"

void InputHandler::onKeyPressed(EventKeyboard::KeyCode key) {
    keyManager.setKey(key);
//    for(Entity* entity: Level.getEntities()) {
//        entity->getCurrentState()->onKeyPressed(entity, key);
//    }
}

void InputHandler::onKeyReleased(EventKeyboard::KeyCode key) {
    keyManager.removeKey(key);
}


