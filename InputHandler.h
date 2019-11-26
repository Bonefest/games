#ifndef INPUTHANDLER_H_INCLUDED
#define INPUTHANDLER_H_INCLUDED

#include "Command.h"
#include "cocos2d.h"
#include "../cocoslib/KeyManager.h"
#include <map>

using std::map;
using std::shared_ptr;

class InputHandler {
public:
	void handleInput(KeyManager& keyManager);
	void setCommandToButton(cocos2d::EventKeyboard::KeyCode,
							shared_ptr<Command> );

private:
	map<cocos2d::EventKeyboard::KeyCode, shared_ptr<Command> > buttons;
};


#endif // INPUTHANDLER_H_INCLUDED
