#include "tile.hpp"

namespace Sudoku {
  Tile::Tile(sf::RenderWindow &window, const sf::Font &font,
	     const sf::Vector2f &tilePosition,
	     const sf::Vector2i &tileSize,
	     const std::vector<Sudoku::Tile *> &group) :
    _window(window), _group(group) {

    _shape = new sf::RectangleShape(sf::Vector2f(tileSize.x - 1,
						tileSize.y - 1));
    _shape->setPosition(tilePosition);

    _text = new sf::Text();
    _text->setFont(font);
    _text->setString(" " + std::to_string(0)); // see how to make dynamic
    _text->setCharacterSize(tileSize.x / 1.5f);
    _text->setFillColor(sf::Color::Black); // see how to make dynamic
    _text->setPosition(tilePosition);

    _value = 0;

  }

  Tile::~Tile() {
    delete _text;
    delete _shape;
  }

  void Tile::draw() {
    _window.draw(*_shape);
    _window.draw(*_text);
  }

  int Tile::getValue() {
    return _value;
  }

  void Tile::setValue(int value) {
    if (value < 0 || value > 9)
      return ;
    _text->setString(" " + std::to_string(value));
    _value = value;
  }
}
