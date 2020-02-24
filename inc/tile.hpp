
#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

namespace Sudoku {
  class Tile {
  public:
    Tile(sf::RenderWindow &window, const sf::Font &font,
	 const sf::Vector2f &tilePosition,
	 const sf::Vector2i &tileSize,
	 const std::vector<Sudoku::Tile *> &group);
    ~Tile();

    void draw();

    int getValue();
    void setValue(int value);
  private:
    sf::RenderWindow &_window;
    sf::Shape *_shape;
    sf::Text *_text;

    int _value;
    std::vector<int> _hint;
    std::vector<Sudoku::Tile *> _group;
  };
}
