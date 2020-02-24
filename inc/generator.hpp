
#pragma once

#include <vector>

namespace Sudoku {
  class Generator {
  public:
    Generator(size_t size = 9);
    ~Generator();


    const std::vector<std::vector<int>> &getBoard();
  private:
    bool isRowValid(size_t row);
    bool isColValid(int col);
    bool fill(size_t row, size_t col);
    bool isValid();

    sf::Vector2i activeSquareStart(size_t row, size_t col);
    std::vector<sf::Vector2i> activeSquareMembers(size_t const row, size_t const col);
    std::vector<bool> numsInSquare(size_t const row, size_t const col);
    bool isSquareValid(size_t const row, size_t const col);

    size_t linesize_;
    std::vector<std::vector<int>> gridElements_;
  };
}
