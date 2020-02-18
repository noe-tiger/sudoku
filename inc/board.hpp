
#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "tile.hpp"

namespace Sudoku {

  class Board {
  public:
    Board(sf::RenderWindow &window);
    ~Board();

    void update(const sf::Event &event);
    void update();
    void draw();
  private:
    void createBoard();
    void createGroup(const sf::Vector2i &tileSize, const int x, const int y);


    sf::RenderWindow &_window;
    sf::Font _font;

    std::vector<Sudoku::Tile *> _tiles;

    std::vector<std::vector<Sudoku::Tile *>> _group;
    std::vector<std::vector<Sudoku::Tile *>> _board;
  };
}
