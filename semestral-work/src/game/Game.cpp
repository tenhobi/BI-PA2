#include <string>
#include <iostream>
#include <fstream>

#include "Game.hpp"

Game::Game (std::string fileName) {}

bool Game::load () {
  std::ifstream inFile;
  inFile.open(fileName, std::ios::in);

  if (!inFile.is_open()) {
    return false;
  }

  inFile.close();

//  map.load(fileName);

  return true;
}

void Game::save () {}

void Game::loop () {}

void Game::start () {}
