#include <iostream>
#include <random>

#include <SFML/Graphics.hpp>

#include "generator.hpp"

bool logical_and(bool x, bool y) {
  return x & y;
}

namespace Sudoku {
  Generator::Generator(size_t size) {
    linesize_ = size; // VOIR POUR FAIRE UNE TAILLE VARIABLE
    srand(time(NULL));
    gridElements_.resize(linesize_, std::vector<int>(linesize_, 0));
    fill(0, 0);
  }

  Generator::~Generator() {}

  const std::vector<std::vector<int>> &Generator::getBoard() {
    return gridElements_;
  }

  bool Generator::isValid() {
    for (size_t i = 0; i < linesize_; i++) {
      if (!isRowValid(i) || !isColValid(i)) {
	return false;
      }
    }
    return true;
  }

  bool Generator::fill(size_t row, size_t col) {
    if (!isValid()) {
      return false;
    }
    if ((row == linesize_) || (col == linesize_)) {
      return true;
    }

    size_t nextCol = (col + 1) % linesize_;
    size_t nextRow = row;
    if (nextCol < col) {
      nextRow++;
    }

    std::vector<bool> attemptedNumbers = numsInSquare(row, col);
    attemptedNumbers[0] = true;
    int value = 0;
    bool triedAllNumbers = false;
    bool restOfGridValid = false;

    while (!triedAllNumbers && !restOfGridValid) {
      while (attemptedNumbers[value]) {
	value = rand() % linesize_ + 1;
      }
      attemptedNumbers[value] = true;
      gridElements_[row][col] = value;

      triedAllNumbers = std::accumulate(attemptedNumbers.begin(),
					attemptedNumbers.end(), true, logical_and);
      restOfGridValid = fill(nextRow, nextCol);
    } 
    if (triedAllNumbers && !restOfGridValid) {
      gridElements_[row][col] = 0;
    }

    return restOfGridValid;
  }

  bool Generator::isRowValid(size_t row) {
    std::vector<bool> numPresent (linesize_ + 1, false);

    for (size_t i = 0; i < linesize_; i++) {
      int element = gridElements_[row][i];

      if (element != 0) {
	if (numPresent[element]) {
	  return false;
	} else {
	  numPresent[element] = true;
	}
      }
    }
    return true;
  }

  bool Generator::isColValid(int col) {
    std::vector<bool> numPresent (linesize_ + 1, false);

    for (size_t i = 0; i < linesize_; i++) {
      int element = gridElements_[i][col];

      if (element != 0) {
	if (numPresent[element]) {
	  return false;
	} else {
	  numPresent[element] = true;
	}
      } else {
	break;
      }
    }
    return true;
  }

  sf::Vector2i Generator::activeSquareStart(size_t row, size_t col) {
    return sf::Vector2i(row - (row % int(std::sqrt(linesize_))),
			col - (col % int(std::sqrt(linesize_))));
  }

  std::vector<sf::Vector2i> Generator::activeSquareMembers(size_t const row, size_t const col) {
    auto [x, y] = activeSquareStart(row, col); 
    std::vector<sf::Vector2i> members;
    members.reserve(linesize_);
    for(size_t i=0; i<sqrt(linesize_); ++i){
      for(size_t j=0; j<sqrt(linesize_); ++j){
	members.push_back(sf::Vector2i(x+i, y+j));
      }
    }
    return members;
  }

  std::vector<bool> Generator::numsInSquare(size_t const row, size_t const col) {
    std::vector<bool> numPresent (linesize_ + 1, false);
    numPresent[0] = true;
    std::vector<sf::Vector2i> squareMembers = activeSquareMembers(row, col);
    for(auto e : squareMembers){
      numPresent[ gridElements_.at(e.x).at(e.y) ] = true;
    }
    return numPresent;
  }

  bool Generator::isSquareValid(size_t const row, size_t const col) {
    std::vector<bool> numPresent = numsInSquare(row, col);
    return std::accumulate(numPresent.begin(), numPresent.end(), true, logical_and);
  }
}
