
#pragma once

#include <SFML/Graphics.hpp>

#include "game.hpp"

namespace Sudoku {
  class Window {
  public:
    Window(const sf::Vector2i &size);
    ~Window();

    bool isOpen();
    void update();
  private:
    Sudoku::Game *_game;

    sf::RenderWindow _window;
  };
}
