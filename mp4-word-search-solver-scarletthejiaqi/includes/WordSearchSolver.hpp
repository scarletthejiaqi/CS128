#ifndef WORDSEARCHSOLVER_HPP
#define WORDSEARCHSOLVER_HPP

#include <cstddef>
#include <string>
#include <vector>

#include "WordLocation.hpp"

enum class CheckDirection { kHorizontal, kVertical, kLeftDiag, kRightDiag };

class WordSearchSolver {
public:
  WordSearchSolver(const std::vector<std::vector<char>>& puzzle);
  WordLocation FindWord(const std::string& word);
  WordLocation FindWord(const std::string& word, CheckDirection direction);
  WordLocation Horizontal(const std::string& word);
  WordLocation Vertical(const std::string& word);
  WordLocation LeftDiag(const std::string& word);
  void LeftDiagUpper(std::string& left_line, size_t& find_col,const std::string& word, int& index);
  WordLocation RightDiag(const std::string& word);
  void RightDiagUpper(std::string& right_line, size_t& find_col,const std::string& word, int& index);

private:
  bool LocationInBounds(size_t row, size_t col) const;
  std::vector<std::vector<char>> puzzle_;
  size_t puzzle_height_;
  size_t puzzle_width_;
};



#endif