#include "board.hpp"

namespace Sudoku {
  Board::Board(sf::RenderWindow &window) : _window(window) {
    createBoard();
    
  }

  Board::~Board() {}

  void Board::update(const sf::Event &event) {

  }

  void Board::update() {

  }

  void Board::draw() {
    // _window.draw(rectangle);
    for (const auto shape : _shapes) {
      _window.draw(*shape);
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
	auto shape = new sf::RectangleShape(sf::Vector2f(tileSize.x - 1,
							 tileSize.y - 1));
	shape->setPosition
	  (sf::Vector2f(x * (tileSize.x + 1) * 3 + i * tileSize.x,
			y * (tileSize.y + 1) * 3 + j * tileSize.y));
	_shapes.push_back(shape);
      }
    }
  }
}
