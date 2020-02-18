#include <iostream>

#include "board.hpp"

namespace Sudoku {
  Board::Board(sf::RenderWindow &window) : _window(window) {
    // find a way to get dynamic string
    if (!_font.loadFromFile("../assets/Trebuchet.ttf")) {
      // exit bc can not load font
    }

    createBoard();


    // PRINT DE TEST POUR LA BOARD GENERATION
    // for (const auto tile : _tiles) {
    //   std::cout << tile->getValue() << " ";
    // }
    // std::cout << std::endl;
    // std::cout << std::endl;

    // for (const auto group : _group) {
    //   for (const auto tile : group) {
    // 	std::cout << tile->getValue() << " ";
    //   }
    //   std::cout << std::endl;
    // }
    // std::cout << std::endl;
    // std::cout << std::endl;

    // for (const auto line : _board) {
    //   for (const auto tile : line) {
    // 	std::cout << tile->getValue() << " ";
    //   }
    //   std::cout << std::endl;
    // }
    // std::cout << std::endl;
    // std::cout << std::endl;
  }

  Board::~Board() {
    // delete all the tiles
  }

  void Board::update(const sf::Event &event) {

  }

  void Board::update() {

  }

  void Board::draw() {
    for (const auto tile : _tiles) {
      tile->draw();
    }
  }

  inline void Board::createBoard() {
    sf::Vector2u windowSize = _window.getSize();
    sf::Vector2i tileSize = sf::Vector2i(windowSize.x / 9, windowSize.y / 9);
    for (int i = 0; i < 9; i += 1) {
      _board.push_back(std::vector<Sudoku::Tile *>());
    }
    for (int x = 0; x < 3; x += 1) {
      for (int y = 0; y < 3; y += 1) {
	_group.push_back(std::vector<Sudoku::Tile *>());
	createGroup(tileSize, x, y);
      }
    }
  }

  inline void Board::createGroup(const sf::Vector2i &tileSize,
				 const int x, const int y) {
    for (int i = 0; i < 3; i += 1) {
      for (int j = 0; j < 3; j += 1) {
	sf::Vector2f tilePosition(x * (tileSize.x + 1) * 3 + i * tileSize.x,
				  y * (tileSize.y + 1) * 3 + j * tileSize.y);
	Sudoku::Tile *tile = new Tile(_window, _font, tilePosition, tileSize, x*3+y + 1 + i + j * 3);
	_tiles.push_back(tile);
	_group[_group.size() - 1].push_back(tile);
	_board[x * 3 + i].push_back(tile);
      }
    }
  }
}
