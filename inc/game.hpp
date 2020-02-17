
#pragma once

#include <SFML/Graphics.hpp>

#include "board.hpp"

namespace Sudoku {
  class Game {
  public:
    Game(sf::RenderWindow &_window);
    ~Game();

    void update(const sf::Event &event);
    void update();
    void draw();
  private:
    sf::RenderWindow &_window;

    Sudoku::Board _board;

    bool menu = true;
  };
}
