
#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "tile.hpp"
#include "generator.hpp"

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

    void getMoves();
    void getCursor();
    void getNumber(const sf::Event &event);
    void removeHints(const int value);

    int _boardSize = 9; // set dynamic

    sf::RenderWindow &_window;
    sf::Font _font; // set dynamic size

    sf::Shape *_playerShape;

    sf::Vector2i _player;

    std::vector<Sudoku::Tile *> _tiles;

    std::vector<std::vector<Sudoku::Tile *>> _group;
    std::vector<std::vector<Sudoku::Tile *>> _board;

    std::vector<std::vector<int>> _raw;
  };
}
