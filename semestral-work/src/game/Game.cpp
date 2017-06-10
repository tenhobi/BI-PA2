#include <string>
#include <iostream>
#include "Game.hpp"

Game::Game (int invasionLimit) : invasionLimit(invasionLimit) {
  this->load();
}

Game::Game (int invasionLimit, Map map) : invasionLimit(invasionLimit), map(map) {
  if (!this->map) {
    this->load();
  }
}

void Game::load () {

}

void Game::start () {

}

void Game::save () const {

}

void Game::loop () {

  if (this->invasionCount < this->invasionLimit) {
    std::string command;

    std::cin >> command;

    if (command == "exit") {
      this->finished = true;
      this->close();
    } else if (command == "save") {
      // save map
    } else if (command == "tower") {
      // tower instructions
    }

    if (!this->finished) {
      this->loop();
    }
  }
}

void Game::close () {

}
