#include <iostream>

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
    _guessed = false;

    for (int i = 0; i < 9; i += 1) {// set dynamic size
      _hint.push_back(false);
      auto text = new sf::Text();
      sf::Vector2f hintPos = sf::Vector2f(tileSize.x / 3 * (i % 3) - 3, tileSize.y / 3 * (i / 3) - 3);
      text->setFont(font);
      text->setCharacterSize(tileSize.x / (1.5f * 2));
      text->setFillColor(sf::Color::Black);
      text->setString(" " + std::to_string(i + 1));
      text->setPosition(tilePosition + hintPos);
      _hintText.push_back(text);
    }
  }

  Tile::~Tile() {
    delete _text;
    delete _shape;
  }

  void Tile::draw() {
    _window.draw(*_shape);
    if (!_guess || _guessed)
      _window.draw(*_text);
    else
      for (int i = 0; i < _hintText.size(); i += 1)
	if (_hint[i])
	  _window.draw(*_hintText[i]);
  }

  int Tile::getValue() {
    if (!_guess)
      return _value;
    if (_guessed)
      return _guessedValue;
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

  void Tile::setGuessedValue(int value) {
    if (!_guess)
      return ;
    _guessedValue = value;
    if (value == 0)
      _guessed = false;
    else
      _guessed = true;
    _text->setString(" " + std::to_string(value)); // see how to make dynamic
  }

  void Tile::setHint(int value) {
    if (value <= 0 || value > 9)
      return ;
    _hint[value - 1] = !_hint[value - 1];
  }

  bool Tile::getHint(int value) {
    if (value <= 0 || value >= 9)
      return false;
    return _hint[value - 1];
  }

  void Tile::highlight(int value) {
    // changer le highlight en fonction d un chiffre pour highlight les hints
    if ((_guessedValue == value || _value == value) && value != 0)
      _text->setFillColor(sf::Color::Red); // highlight
    else {
      if (_guessed)
	_text->setFillColor(sf::Color::Blue); // modified by the player
      else
	_text->setFillColor(sf::Color::Black); // fixed tile
    }
    for (const auto hint : _hintText)
      hint->setFillColor(sf::Color::Black);
    if (value > 0 && value <= 9)
      _hintText[value - 1]->setFillColor(sf::Color::Red);
    _shape->setFillColor(sf::Color(255, 255, 255, 255));
  }

  void Tile::highlight() {
    _shape->setFillColor(sf::Color(255, 255, 128, 255));
  }
}
