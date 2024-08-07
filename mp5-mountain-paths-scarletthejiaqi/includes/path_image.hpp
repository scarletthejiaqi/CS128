#ifndef PATH_IMAGE_H
#define PATH_IMAGE_H

#include <cstdlib>  // for size_t
#include <vector>

#include "color.hpp"
#include "path.hpp"
#include "grayscale_image.hpp"
#include "elevation_dataset.hpp"
#include "path.hpp"
#include <vector>
struct PathImageHelperParams {
    int& mini;
    unsigned int& cur_row;
    unsigned int& col;
    const ElevationDataset& dataset;
    Path& path;
    int& change_up;
    int& change_mid;
    int& change_down;
};
class PathImage {
public:
  PathImage(const GrayscaleImage& image, const ElevationDataset& dataset);
  size_t Width() const {return width_;}
  size_t Height() const  {return height_;}
  unsigned int MaxColorValue() const {return kMaxColorValue;}
  const std::vector<Path>& Paths() const {return paths_;}
  const std::vector<std::vector<Color>>& GetPathImage() const {return path_image_;}
  void ToPpm(const std::string& name) const;
  // write behavior declarations here; define in path_image.cc.
  void HelperNormal(PathImageHelperParams para);
  void HelperFirstLine(PathImageHelperParams para);
  void HelperLastLine(PathImageHelperParams para);
  void ColorIt(std::vector<Path>& paths_,std::vector<std::vector<Color>>& path_image_,unsigned int& best_path_row);

private:
  std::vector<Path> paths_;
  size_t width_ = 0;
  size_t height_ = 0;
  std::vector<std::vector<Color>> path_image_;
  static const int kMaxColorValue = 255;
};

#endif