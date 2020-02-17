#include "window.hpp"

int main() {
  Sudoku::Window window(sf::Vector2i(600, 600));

  while (window.isOpen()) {
    window.update();
  }
  return 0;
}
