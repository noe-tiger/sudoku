#include "board.hpp"

namespace Sudoku {
  Board::Board(sf::RenderWindow &window) : _window(window) {
    // find a way to get dynamic string
    if (!_font.loadFromFile("../assets/Trebuchet.ttf")) {
      // exit bc can not load font
    }

    createBoard();
  }

  Board::~Board() {}

  void Board::update(const sf::Event &event) {

  }

  void Board::update() {

  }

  void Board::draw() {
    // _window.draw(rectangle);
    for (const auto tile : _tiles) {
      _window.draw(*(tile->shape));
      _window.draw(*(tile->text));
    }
  }

  inline void Board::createBoard() {
    sf::Vector2u windowSize = _window.getSize();
    sf::Vector2i tileSize = sf::Vector2i(windowSize.x / 9, windowSize.y / 9);
    for (int x = 0; x < 3; x += 1) {
      for (int y = 0; y < 3; y += 1) {
	createGroup(tileSize, x, y);
      }
    }
  }

  inline void Board::createGroup(const sf::Vector2i &tileSize,
				 const int x, const int y) {
    for (int i = 0; i < 3; i += 1) {
      for (int j = 0; j < 3; j += 1) {
	Sudoku::Tile *tile = new Tile;
	sf::Vector2f tilePosition(x * (tileSize.x + 1) * 3 + i * tileSize.x,
				  y * (tileSize.y + 1) * 3 + j * tileSize.y);
	tile->shape = new sf::RectangleShape(sf::Vector2f(tileSize.x - 1,
							 tileSize.y - 1));
	tile->shape->setPosition(tilePosition);

	tile->text = new sf::Text();
	tile->text->setFont(_font);
	tile->text->setString(" " + std::to_string(1 + i + j * 3)); // see how to make dynamic
	tile->text->setCharacterSize(tileSize.x / 1.5f);
	tile->text->setFillColor(sf::Color::Black); // see how to make dynamic
	tile->text->setPosition(tilePosition);

	_tiles.push_back(tile);
      }
    }
  }
}
