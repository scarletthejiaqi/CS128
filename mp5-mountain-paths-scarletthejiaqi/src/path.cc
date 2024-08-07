#include "path.hpp"
#include <vector>
#include <stdexcept>

Path::Path(size_t length, size_t starting_row) {
    length_ = length;
    starting_row_ = starting_row;
    path_.resize(length_);
}

void Path::IncEleChange(unsigned int value) {
    if (value < 0) {
        throw std::runtime_error("value should be positive");
    }
    ele_change_ += value;
}

void Path::SetLoc(size_t col, size_t row) {
    path_.at(col) = row;
}