#include "InputHandler.h"
#include <iostream>

void InputHandler::handleInput(KeyManager& keyManager) {
    for(auto& button : buttons) {
        if(keyManager.isKeyPressed(button.first)) {

        std::cout << int(button.first) << std::endl;
            button.second->execute();
        }
    }
}

void InputHandler::setCommandToButton(cocos2d::EventKeyboard::KeyCode key, shared_ptr<Command> command) {
    buttons[key] = command;
}
