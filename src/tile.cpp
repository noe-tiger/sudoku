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

    _value = 0;

    _text = new sf::Text();
    _text->setFont(font);
    _text->setString(" " + std::to_string(_value)); // see how to make dynamic
    _text->setCharacterSize(tileSize.x / 1.5f);
    _text->setFillColor(sf::Color::Black); // see how to make dynamic
    _text->setPosition(tilePosition);

    _guess = false;
  }

  Tile::~Tile() {
    delete _text;
    delete _shape;
  }

  void Tile::draw() {
    _window.draw(*_shape);
    if (!_guess)
      _window.draw(*_text);
    else
      return ; // replace with drawing the guessed number / the hints
  }

  int Tile::getValue() {
    if (!_guess)
      return _value;
    return 0;
  }

  void Tile::setValue(int value) {
    if (_value != 0 && !_guess)
      return ;
    if (value < 0 || value > 9) // changer si grille plus grande
      return ;
    _text->setString(" " + std::to_string(value));
    _value = value;
  }

  void Tile::setGuess(bool guess) {
    _guess = guess;
  }

  void Tile::highlight(bool highlight) {
    if (highlight)
      _text->setFillColor(sf::Color::Red);
    else
      _text->setFillColor(sf::Color::Black);
  }
}
