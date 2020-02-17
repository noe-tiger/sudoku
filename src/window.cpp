#include "window.hpp"

namespace Sudoku {
  Window::Window(const sf::Vector2i &size) {
    _window.create(sf::VideoMode(size.x, size.y), "Sudoku");
    _window.setFramerateLimit(60);
    _game = new Sudoku::Game(_window);
  }

  Window::~Window() {
    delete _game;
  }

  bool Window::isOpen() {
    sf::Event event;

    while (_window.pollEvent(event)) {
      if (event.type == sf::Event::Closed ||
	  sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	_window.close();
      _game->update(event);
    }
    _game->update();
    if (!_window.isOpen()) {
      return false;
    }
    return true;
  }

  void Window::update() {
    _window.clear(sf::Color::Black);
    _game->draw();
    _window.display();
  }
}
