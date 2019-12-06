#include "Game.h"

Game* Game::getInstance() {
    static Game _instance;
    return &_instance;
}

void Game::initGameWithScene(Scene* scene) {
    setCurrentScene(scene);
}

void Game::setCurrentScene(Scene* scene) {
    currentScene = scene;
}

void Game::setPlayer(Entity* player) {
    this->player = player;
}

Entity* Game::getPlayer() {
    return player;
}
