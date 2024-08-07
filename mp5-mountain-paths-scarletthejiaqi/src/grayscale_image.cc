#include "grayscale_image.hpp"
#include <cmath>
#include <iostream>
#include <fstream>
#include "elevation_dataset.hpp"
#include "color.hpp"

GrayscaleImage::GrayscaleImage(const std::string& filename, size_t width, size_t height) {
    width_ = width;
    height_ = height;
    image_.resize(height_, std::vector<Color>(width_));
    ElevationDataset dataset = ElevationDataset(filename, width_, height_);
    for (unsigned int row = 0; row < dataset.Height(); ++row) {
        for (unsigned int col = 0; col < dataset.Width(); ++col) {
            if (dataset.MaxEle() - dataset.MinEle() == 0) {
                image_.at(row).at(col) = Color(0,0,0);
                continue;
            }
            int shade_of_gray = static_cast<int>(std::round(static_cast<double>(dataset.DatumAt(row,col) - dataset.MinEle()) / (dataset.MaxEle() - dataset.MinEle())*(kMaxColorValue)));

            image_.at(row).at(col) = Color(shade_of_gray,shade_of_gray,shade_of_gray);
        }
    }
}

GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset){
    width_ = dataset.Width();
    height_ = dataset.Height();
    image_.resize(height_, std::vector<Color>(width_));
    for (unsigned int row = 0; row < dataset.Height(); ++row) {
        for (unsigned int col = 0; col < dataset.Width(); ++col) {
            if (dataset.MaxEle() - dataset.MinEle() == 0) {
                image_.at(row).at(col) = Color(0,0,0);
                continue;
            }
            int shade_of_gray = static_cast<int>(std::round(static_cast<double>(dataset.DatumAt(row,col) - dataset.MinEle()) / (dataset.MaxEle() - dataset.MinEle())*(kMaxColorValue)));
            image_.at(row).at(col) = Color(shade_of_gray,shade_of_gray,shade_of_gray);
        }
    }
}

void GrayscaleImage::ToPpm(const std::string& name) const {
    std::ofstream ofs(name);
    ofs<<"P3\n"<<width_<<" "<<height_<<"\n"<<kMaxColorValue<<"\n";
    for (unsigned int row = 0; row < height_; ++row) {
        for (unsigned int col = 0; col < width_; ++col) {
            ofs<< image_.at(row).at(col).Red() << " "<< image_.at(row).at(col).Green() << " "<< image_.at(row).at(col).Blue()<<" ";
        }
        ofs<<"\n";
    }
}