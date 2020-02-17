#include "game.hpp"

namespace Sudoku {
  Game::Game(sf::RenderWindow &window) : _window(window), _board(window) {
  }

  Game::~Game() {}

  void Game::update(const sf::Event &event) {
    // if (menu) {
    //   _menu.update(event);
    // } else {
      _board.update(event);
    // }

  }

  void Game::update() {
    // if (menu) {
    //   _menu.update();
    // } else {
      _board.update();
    // }

  }

  void Game::draw() {
    // if (menu) {
    //   _menu.draw();
    // } else {
      _board.draw();
    // }
  }
}
