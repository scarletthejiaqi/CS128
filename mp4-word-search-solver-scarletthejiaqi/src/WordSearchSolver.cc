#include "WordSearchSolver.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <cstddef>

std::vector<CharPositions> char_positions;

bool WordSearchSolver::LocationInBounds(size_t row, size_t col) const {
  return ((row < puzzle_height_) && (col < puzzle_width_));
}

WordSearchSolver::WordSearchSolver(const std::vector<std::vector<char>>& puzzle) {
  puzzle_ = puzzle;
  puzzle_height_ = puzzle.size();
  puzzle_width_ = puzzle.at(0).size();
}

//problem right here
WordLocation WordSearchSolver::FindWord(const std::string& word) {
  WordLocation h = WordSearchSolver::FindWord(word,CheckDirection::kHorizontal);
  if (!h.word.empty()) {
    return h;
  } 
  WordLocation v = WordSearchSolver::FindWord(word,CheckDirection::kVertical);
  if (!v.word.empty()) {
    return v;
  } 
  WordLocation l = WordSearchSolver::FindWord(word,CheckDirection::kLeftDiag);
  if (!l.word.empty()) {
    return l;
  }
  WordLocation r = WordSearchSolver::FindWord(word,CheckDirection::kRightDiag);
  if (!r.word.empty()) {
    return r;
  }
  return WordLocation{};
}

WordLocation WordSearchSolver::FindWord(const std::string& word, CheckDirection direction) {
    switch (direction) {
      case CheckDirection::kHorizontal :
        return Horizontal(word);
        break;
      case CheckDirection::kVertical :
        return Vertical(word);
        break;
      case CheckDirection::kLeftDiag:
        return LeftDiag(word);
        break;
      case CheckDirection::kRightDiag :
        return RightDiag(word);
        break;
    }
  }
    


//helper functions


WordLocation WordSearchSolver::Horizontal(const std::string& word) {
  std::string hori_line;
  int index = -1;
  size_t find_row = 0;
  for (size_t row = 0; row < puzzle_height_; ++row) {
    for (size_t col = 0; col < puzzle_width_; ++col) {
      hori_line += puzzle_.at(row).at(col);
    }
    size_t n = hori_line.find(word);
    if (std::string::npos == n) {
      hori_line = "";
      continue;
      } 
      index = static_cast<int>(n);
      find_row = row;
      break;
  }
  if (index == -1) {
    return WordLocation{};
  }
  char_positions.clear();
  for (unsigned int i = index; i < word.size() + index; ++i) {
    char_positions.push_back(CharPositions{hori_line.at(i),find_row,i});
  }
  return WordLocation{word,char_positions};
}

WordLocation WordSearchSolver::Vertical(const std::string& word) {
  std::string vert_line;
  int index = -1;
  size_t find_col = 0;
  for (size_t col = 0; col < puzzle_width_; ++col) {
    for (size_t row = 0; row < puzzle_height_; ++row) {
      vert_line += puzzle_.at(row).at(col);
    }
    size_t n = vert_line.find(word);
    if (std::string::npos == n) {
      vert_line = "";
      continue;
    } 
    index = static_cast<int>(n);
    find_col = col;
    break;
  }
  if (index == -1) {
    return WordLocation{};
  }
  char_positions.clear();
  for (unsigned int i = index; i < word.size() + index; ++i) {
    char_positions.push_back(CharPositions{vert_line.at(i),i,find_col});
  }
  return WordLocation{word,char_positions};
}

WordLocation WordSearchSolver::LeftDiag(const std::string& word) {
  std::string left_line;
  int index = -1;
  size_t find_col = 0;
  WordSearchSolver::LeftDiagUpper(left_line, find_col, word, index);
  char_positions.clear();
  if (index != -1) {
    for (unsigned int i = index; i < word.size() + index; ++i) {
    char_positions.push_back(CharPositions{left_line.at(i),i,find_col - i});
    }
    return WordLocation{word,char_positions};
  }
  //next part
  size_t find_row = 0;
  for (size_t row = 1; row < puzzle_height_; ++row) {
    size_t r = row;
    size_t c = puzzle_width_ - 1;
    while (r < puzzle_height_ && r != std::numeric_limits<size_t>::max() && c != std::numeric_limits<size_t>::max()) {
      left_line += puzzle_.at(r).at(c);
      ++r;
      --c;
    }
    size_t n = left_line.find(word);
    if (std::string::npos == n) {
      left_line = "";
      continue;
      } 
    index = static_cast<int>(n);
    find_row = row;
    break;
    }
    char_positions.clear();
    if (index != -1) {
    for (unsigned int i = index; i < word.size() + index; ++i) {
    char_positions.push_back(CharPositions{left_line.at(i),find_row - i,puzzle_width_ - 1 - i});
    }
    return WordLocation{word,char_positions};
  }
  return WordLocation{};
}

void WordSearchSolver::LeftDiagUpper(std::string& left_line, size_t& find_col,const std::string& word, int& index) {
  for (size_t col = 0; col < puzzle_width_; ++col) {
    size_t c = col;
    size_t r = 0;
    while (r < puzzle_height_ && r != std::numeric_limits<size_t>::max() && c != std::numeric_limits<size_t>::max()) {
      left_line += puzzle_.at(r).at(c);
      ++r;
      --c;
    }
    size_t n = left_line.find(word);
    if (std::string::npos == n) {
      left_line = "";
      continue;
      } 
      index = static_cast<int>(n);
      find_col = col;
      break;
  }
}

WordLocation WordSearchSolver::RightDiag(const std::string& word) {
  std::string right_line;
  int index = -1;
  size_t find_col = 0;
  WordSearchSolver::RightDiagUpper(right_line, find_col, word, index);
  char_positions.clear();
  if (index != -1) {
    for (unsigned int i = index; i < word.size() + index; ++i) {
    char_positions.push_back(CharPositions{right_line.at(i),i,find_col + i});
    }
    return WordLocation{word,char_positions};
  }
  //next part
  size_t find_row = 0;
  for (size_t row = 1; row < puzzle_height_; ++row) {
    size_t r = row;
    size_t c = 0;
    while (r < puzzle_height_ && c < puzzle_width_) {
      right_line += puzzle_.at(r).at(c);
      ++r;
      ++c;
    }
    size_t n = right_line.find(word);
    if (std::string::npos == n) {
      right_line = "";
      continue;
      } 
    index = static_cast<int>(n);
    find_row = row;
    break;
    }
    char_positions.clear();
    if (index != -1) {
    for (unsigned int i = index; i < word.size() + index; ++i) {
    char_positions.push_back(CharPositions{right_line.at(i),find_row + i,i});
    }
    return WordLocation{word,char_positions};
  }
  return WordLocation{};
}

void WordSearchSolver::RightDiagUpper(std::string& right_line, size_t& find_col,const std::string& word, int& index) {
  for (size_t col = 0; col < puzzle_width_; ++col) {
    size_t c = col;
    size_t r = 0;
    while (r < puzzle_height_ && c < puzzle_width_) {
      right_line += puzzle_.at(r).at(c);
      ++r;
      ++c;
    }
    size_t n = right_line.find(word);
    if (std::string::npos == n) {
      right_line = "";
      continue;
      } 
      index = static_cast<int>(n);
      find_col = col;
      break;
  }
}