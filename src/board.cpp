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
    for (int i = 0; i < 81 - 35; i += 1) // set the difficulty (30 = medium)
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
    getNumber(event);    
  }

  void Board::update() {
    getMoves();
    
    // faire ca plus propre
    sf::Vector2i tileSize = sf::Vector2i(_window.getSize().x / _boardSize,
					 _window.getSize().y / _boardSize); // set dynamically
    sf::Vector2f tilePosition
      ((3 * static_cast<int>(_player.x / sqrt(_boardSize))) + _player.x * tileSize.x,
       (3 * static_cast<int>(_player.y / sqrt(_boardSize))) + _player.y * tileSize.y); // faire plus mieux
    _playerShape->setPosition(tilePosition);

    int val = _board[_player.x][_player.y]->getValue();
    std::cout << val << std::endl;
    for (const auto tile : _tiles) {
      tile->highlight(val);
      // if (tile->getValue() == val)
      // 	tile->highlight(true);
      // else
      // 	tile->highlight(false);
    }
    for (int i = 0; i < _boardSize; i += 1) {
      _board[_player.x][i]->highlight();
      _board[i][_player.y]->highlight();
    }
    for (int i = 0; i < _group[_player.x / 3 * 3 + _player.y / 3].size(); i += 1) {
      _group[_player.x / 3 * 3 + _player.y / 3][i]->highlight();
    }
  }

  inline void Board::getNumber(const sf::Event &event) {
    if (event.type == sf::Event::TextEntered) {
      if (event.text.unicode >= '0' && event.text.unicode <= '9') {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
	  _board[_player.x][_player.y]->setHint(static_cast<int>(event.text.unicode - '0'));
	else
	  _board[_player.x][_player.y]->setGuessedValue(static_cast<int>(event.text.unicode - '0'));
      } else if (event.text.unicode == 8) {
	_board[_player.x][_player.y]->setGuessedValue(0);
      }
    }
  }

  inline void Board::getMoves() {
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
