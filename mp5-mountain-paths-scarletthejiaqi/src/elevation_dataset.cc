#include "elevation_dataset.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <limits>
ElevationDataset::ElevationDataset(const std::string& filename, size_t width, size_t height) {
    width_ = width;
    height_ = height;
    data_.resize(height_, std::vector<int>(width_));
    std::ifstream ifs(filename);
    int each = 0;
    max_ele_ = INT32_MIN;
    min_ele_ = INT32_MAX;
    for (unsigned int row = 0; row < height_; ++row) {
        for (unsigned int col = 0; col < width_; ++col) {
            if (!ifs.is_open()) {
                throw std::runtime_error("not open");
            }
            ifs>>each;
            if (ifs.fail()) {
                throw std::runtime_error("read fail");
            }
            if (each > max_ele_) {
                max_ele_ = each;
            }
            if (each < min_ele_) {
                min_ele_ = each;
            }
            data_.at(row).at(col) = each;
        }
    } 
    while (ifs>>each) {
        if (ifs.good()) {
            throw std::runtime_error("too much data");
        }
        break;
    }
}

