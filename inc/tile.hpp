
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
    void setGuess(bool guess);

    void setGuessedValue(int value);
    void setHint(int value);
    bool getHint(int value);

    void highlight(int value);
    void highlight();
  private:
    sf::RenderWindow &_window;
    sf::Shape *_shape;
    sf::Text *_text;

    int _value, _guessedValue;

    std::vector<bool> _hint;
    std::vector<sf::Text *> _hintText;

    std::vector<Sudoku::Tile *> _group;
    bool _guess, _guessed;
  };
}
