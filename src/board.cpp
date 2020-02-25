#include <iostream>
#include <math.h>

#include "board.hpp"

namespace Sudoku {
  Board::Board(sf::RenderWindow &window) : _window(window) {
    // find a way to get dynamic string
    if (!_font.loadFromFile("../assets/Trebuchet.ttf")) {
      // exit bc can not load font
    }

    Sudoku::Generator generator;
    _raw = generator.getBoard();

    createBoard();

    // set the emptying differently to make only one solution
    std::random_shuffle(_tiles.begin(), _tiles.end());
    for (int i = 0; i < 81 - 30; i += 1) // set the difficulty (30 = medium)
    	_tiles[i]->setGuess(true);

    _player = sf::Vector2i(4, 4); // set dynamically
    sf::Vector2i tileSize = sf::Vector2i(_window.getSize().x / _boardSize,
					 _window.getSize().y / _boardSize); // set dynamically
    _playerShape = new sf::RectangleShape(sf::Vector2f(tileSize.x - 1,
						       tileSize.y - 1));
    _playerShape->setFillColor(sf::Color(0, 0, 255, 128));
  }

  Board::~Board() {
    // delete all the tiles
  }

  void Board::update(const sf::Event &event) {
    
  }

  void Board::update() {
    static bool left = false, right = false, up = false, down = false;
    // dynamically set keys
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !left) {
      if (_player.x > 0)
	_player.x -= 1;
      left = !left;
    } else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && left)
      left = !left;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !right) {
      if (_player.x < _boardSize - 1)
	_player.x += 1;
      right = !right;
    } else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && right)
      right = !right;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !up) {
      if (_player.y > 0)
	_player.y -= 1;
      up = !up;
    } else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && up)
      up = !up;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !down) {
      if (_player.y < _boardSize - 1)
	_player.y += 1;
      down = !down;
    } else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && down)
      down = !down;


    // faire ca plus propre
    sf::Vector2i tileSize = sf::Vector2i(_window.getSize().x / _boardSize,
					 _window.getSize().y / _boardSize); // set dynamically
    sf::Vector2f tilePosition
      ((3 * int(_player.x / sqrt(_boardSize))) + _player.x * tileSize.x,
       (3 * int(_player.y / sqrt(_boardSize))) + _player.y * tileSize.y); // faire plus mieux
    _playerShape->setPosition(tilePosition);

    int val = _board[_player.x][_player.y]->getValue();
    for (const auto tile : _tiles) {
      if (tile->getValue() == val)
	tile->highlight(true);
      else
	tile->highlight(false);
    }
  }

  void Board::draw() {
    for (const auto tile : _tiles) {
      tile->draw();
    }
    _window.draw(*_playerShape);
  }

  inline void Board::createBoard() {
    sf::Vector2u windowSize = _window.getSize();
    sf::Vector2i tileSize = sf::Vector2i(windowSize.x / _boardSize, windowSize.y / _boardSize);
    for (int i = 0; i < _boardSize; i += 1) {
      _board.push_back(std::vector<Sudoku::Tile *>());
    }
    for (int x = 0; x < sqrt(_boardSize); x += 1) {
      for (int y = 0; y < sqrt(_boardSize); y += 1) {
	_group.push_back(std::vector<Sudoku::Tile *>());
	createGroup(tileSize, x, y);
      }
    }
  }

  inline void Board::createGroup(const sf::Vector2i &tileSize,
				 const int x, const int y) {
    for (int i = 0; i < sqrt(_boardSize); i += 1) {
      for (int j = 0; j < sqrt(_boardSize); j += 1) {
	sf::Vector2f tilePosition(x * (tileSize.x + 1) * sqrt(_boardSize) + i * tileSize.x,
				  y * (tileSize.y + 1) * sqrt(_boardSize) + j * tileSize.y);
	Sudoku::Tile *tile = new Tile(_window, _font, tilePosition,
				      tileSize, _group[_group.size() - 1]);
	tile->setValue(_raw[x * sqrt(_boardSize) + i][y * sqrt(_boardSize) + j]);
	_tiles.push_back(tile);
	_group[_group.size() - 1].push_back(tile);
	_board[x * sqrt(_boardSize) + i].push_back(tile);
      }
    }
  }
}
