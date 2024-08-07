#include "path_image.hpp"
#include "grayscale_image.hpp"
#include "elevation_dataset.hpp"
#include "color.hpp"
#include "path.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cmath>
#include <limits>
PathImage::PathImage(const GrayscaleImage& image, const ElevationDataset& dataset) {
    //dataset part
    unsigned int best_path_row = 0;
    unsigned int best_change = INT32_MAX;
    int change_up = 0;
    int change_mid = 0;
    int change_down = 0;
    int mini = 0;
    unsigned int cur_row = 0;
    for (unsigned int row = 0; row < dataset.Height(); ++row) {
        Path path(dataset.Width(),row);
        path.SetLoc(0, row);
        cur_row = row;
        for (unsigned int col = 0; col < dataset.Width() - 1; ++col) {
            PathImageHelperParams para = {mini,cur_row,col,dataset,path, change_up,change_mid,change_down};
            if (cur_row>0 && cur_row<dataset.Height() - 1) {
                HelperNormal(para);
            } else if (cur_row == 0) {
                HelperFirstLine(para);
                
            } else {
                HelperLastLine(para);
            }
        }
        paths_.push_back(path);
        if (path.EleChange() < best_change) {
                best_change = path.EleChange();
                best_path_row = row;
            }
    }
    // color part
    path_image_ = image.GetImage();
    width_ = image.Width();
    height_ = image.Height();
    ColorIt(paths_,path_image_, best_path_row);

    
}


void PathImage::HelperNormal(PathImageHelperParams para){
                para.change_up = abs(para.dataset.DatumAt(para.cur_row,para.col) - para.dataset.DatumAt(para.cur_row-1,para.col+1));
                para.change_mid = abs(para.dataset.DatumAt(para.cur_row,para.col) - para.dataset.DatumAt(para.cur_row,para.col+1));
                para.change_down = abs(para.dataset.DatumAt(para.cur_row,para.col) - para.dataset.DatumAt(para.cur_row+1,para.col+1));
                para.mini = static_cast<int>(fmin(para.change_up,para.change_down));
                para.mini = static_cast<int>(fmin(para.mini,para.change_mid));
                para.path.IncEleChange(para.mini);
                if (para.mini == para.change_mid) {
                    para.path.SetLoc(para.col+1, para.cur_row);
                } else if (para.mini == para.change_down) {
                    para.path.SetLoc(para.col+1, para.cur_row+1);
                    para.cur_row += 1;
                } else {
                    para.path.SetLoc(para.col+1, para.cur_row-1);
                    para.cur_row -= 1;
                }
}

void PathImage::HelperFirstLine(PathImageHelperParams para){
                para.change_down = abs(para.dataset.DatumAt(para.cur_row,para.col) - para.dataset.DatumAt(para.cur_row+1,para.col+1));
                para.change_mid = abs(para.dataset.DatumAt(para.cur_row,para.col) - para.dataset.DatumAt(para.cur_row,para.col+1));
                para.mini = static_cast<int>(fmin(para.change_down,para.change_mid));
                para.path.IncEleChange(para.mini);
                if (para.mini == para.change_mid) {
                    para.path.SetLoc(para.col+1, para.cur_row);
                } else {
                    para.path.SetLoc(para.col+1, para.cur_row+1);
                    para.cur_row += 1;
                }
}

void PathImage::HelperLastLine(PathImageHelperParams para){
                para.change_mid = abs(para.dataset.DatumAt(para.cur_row,para.col) - para.dataset.DatumAt(para.cur_row,para.col+1));
                para.change_up = abs(para.dataset.DatumAt(para.cur_row,para.col) - para.dataset.DatumAt(para.cur_row-1,para.col+1));
                para.mini = static_cast<int>(fmin(para.change_up,para.change_mid));
                para.path.IncEleChange(para.mini);
                if (para.mini == para.change_mid) {
                    para.path.SetLoc(para.col+1, para.cur_row);
                } else {
                    para.path.SetLoc(para.col+1, para.cur_row-1);
                    para.cur_row -= 1;
                }
}
const int kREDr = 252;
const int kREDg = 25;
const int kREDb = 63;
const int kGREENr = 31;
const int kGREENg = 253;
const int kGREENb = 13;
void PathImage::ColorIt(std::vector<Path>& paths_,std::vector<std::vector<Color>>& path_image_,unsigned int& best_path_row){
    for (unsigned int num = 0; num < paths_.size(); ++num) {
        std::vector<size_t> eachpath= paths_.at(num).GetPath();
        for (unsigned int i = 0; i < eachpath.size(); ++i) {
            path_image_.at(eachpath.at(i)).at(i) = Color(kREDr,kREDg,kREDb);
        }
    }
    std::vector<size_t>  greenrow = paths_.at(best_path_row).GetPath();
    for (unsigned int i = 0; i < greenrow.size(); ++i) {
            path_image_.at(greenrow.at(i)).at(i) = Color(kGREENr,kGREENg,kGREENb);
        }
}
    


void PathImage::ToPpm(const std::string& name) const {
    std::ofstream ofs(name);
    ofs<<"P3\n"<<width_<<" "<<height_<<"\n"<<kMaxColorValue<<"\n";
    for (unsigned int row = 0; row < height_; ++row) {
        for (unsigned int col = 0; col < width_; ++col) {
            ofs<< path_image_.at(row).at(col).Red() << " "<< path_image_.at(row).at(col).Green() << " "<< path_image_.at(row).at(col).Blue()<< " ";
        }
        ofs<<"\n";
    }
}