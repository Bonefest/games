#ifndef INPUTHANDLER_H_INCLUDED
#define INPUTHANDLER_H_INCLUDED

#include "../cocoslib/KeyManager.h"

USING_NS_CC;


class InputHandler {
public:
    void onKeyPressed(EventKeyboard::KeyCode key);
    void onKeyReleased(EventKeyboard::KeyCode key);

    void handleInput();
private:
    KeyManager keyManager;
    //stack<Command*> activatedCommands;
};

#endif // INPUTHANDLER_H_INCLUDED
