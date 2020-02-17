
#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

namespace Sudoku {
  struct Tile {
    sf::Shape *shape;
    sf::Text *text;

    int value;
  };

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
  };
}
