#include "seam_carver.hpp"

// implement the rest of SeamCarver's functions here

 int SeamCarver::GetEnergy(int row, int col) const {
  if (row < 0 || col < 0 || row >= height_ || col >= width_) {
    return INT32_MAX;
  }
  int up = (row + height_ - 1) % height_;
  int down = (row + height_ + 1) % height_;
  int leftcol = (col + width_ - 1) % width_;
  int rightcol = (col + width_ + 1) % width_;
  int rcol = image_.GetPixel(row,leftcol).GetRed() - image_.GetPixel(row,rightcol).GetRed();
  int gcol = image_.GetPixel(row,leftcol).GetGreen() - image_.GetPixel(row,rightcol).GetGreen();
  int bcol = image_.GetPixel(row,leftcol).GetBlue() - image_.GetPixel(row,rightcol).GetBlue();
  int delta_col = rcol*rcol + gcol*gcol + bcol*bcol;
  int rrow = image_.GetPixel(up,col).GetRed() - image_.GetPixel(down,col).GetRed();
  int grow = image_.GetPixel(up,col).GetGreen() - image_.GetPixel(down,col).GetGreen();
  int brow = image_.GetPixel(up,col).GetBlue() - image_.GetPixel(down,col).GetBlue();
  int delta_row = rrow*rrow + grow*grow + brow*brow;
  int e = delta_col + delta_row;
  return e;
 }

int* SeamCarver::GetHorizontalSeam() const {
  int* data = new int[width_];
  int** value = new int*[height_];
  for (int i = 0; i < height_; ++i) {
    value[i] = new int[width_];
  }
  
  for (int col = width_ - 1; col >= 0; --col) {
    for (int row = 0; row < height_; ++row) {
      if (col == (width_ - 1)) {
        value[row][col] = GetEnergy(row,col);
      } else {
        int smaller = value[row][col + 1];
        if (row != 0 && smaller > value[row - 1][col + 1]) {
          smaller = value[row - 1][col + 1];
        } 
        if (row != height_ - 1 && smaller > value[row + 1][col + 1]) {
          smaller = value[row + 1][col + 1];
        }
        value[row][col] = smaller + GetEnergy(row,col);
      }
    }
  }
  FindHorizontalSeam(data,value);
  for (int i = 0; i < height_; ++i) {
    //for (int j = 0; j < width_; ++j) {
      std::cout<<value[i][2]<<std::endl;
    //}
  }
  for (int i = 0; i < width_; ++i) {
    std::cout<<"data is "<<data[i]<<" ";
  } 
  for(int i = 0; i < height_; ++i) {
    delete[] value[i];
  }
  delete[] value;
  value = nullptr;
  for (int i = 0; i < width_; ++i) {
  }
  return data;
}

int* SeamCarver::GetVerticalSeam() const {
  int* data = new int[height_];
  int** value = new int*[height_];
  for (int i = 0; i < height_; ++i) {
    value[i] = new int[width_];
  }
  for (int row = height_ - 1; row >= 0; --row) {
    for (int col = 0; col < width_; ++col) {
      if (row == (height_ - 1)) {
        value[row][col] = GetEnergy(row,col);
      } else {
        int smaller = value[row+1][col];
        if (col != 0 && smaller > value[row+1][col - 1]) {
          smaller = value[row+1][col - 1];
        } 
        if (col != width_ - 1 && smaller > value[row+1][col+1]) {
          smaller = value[row+1][col+1];
        }
        value[row][col] = smaller + GetEnergy(row,col);
      }
    }
  }
  FindVerticalSeam(data, value);
  for(int i = 0; i < height_; ++i) {
    delete[] value[i];
  }
  delete[] value;
  value = nullptr;
  return data;
}

//helper function
void SeamCarver::FindVerticalSeam(int*& data, int**& value) const{
  int smallest = value[0][0];
  int index = 0;
  for (int col = 0; col < width_; ++col) {
    if (value[0][col] < smallest){
      smallest = value[0][col];
      index = col;
    }
  }
  data[0] = index;
  for (int row = 1; row < height_; ++row) {
    if (index == 0) {
      if (value[row][index + 1] < value[row][index]) {
        index = 1;
      }
    } else if(index == (width_ - 1)) {
      if (value[row][index - 1] < value[row][index]) {
        index = index - 1;
      }
    } else {
      if (value[row][index - 1] < value[row][index] && value[row][index - 1] <= value[row][index + 1]) {
        index -= 1;
      } else if (value[row][index + 1] < value[row][index] && value[row][index + 1] < value[row][index - 1]) {
        index += 1;
      }
    }
    data[row] = index;
  }
}

void SeamCarver::FindHorizontalSeam(int*& data, int**& value) const {
  int smallest = value[0][0];
  int index = 0;
  for (int row = 0; row < height_; ++row) {
    if (value[row][0] < smallest) {
      smallest = value[row][0];
      index = row;
    }
  }
  data[0] = index;
  for (int col = 1; col < width_; ++col) {
    if (index == 0) {
      if (value[index + 1][col] < value[index][col]) {
        index = 1;
      }
    } else if(index == (height_ - 1)) {
      if (value[index - 1][col] < value[index][col]) {
        index = index - 1;
      }
    } else {
      if (value[index - 1][col] < value[index][col] && value[index - 1][col] <= value[index + 1][col]) {
        index -= 1;
      } else if (value[index + 1][col] < value[index][col] && value[index + 1][col] < value[index - 1][col]) {
        index += 1;
      }
    }
    data[col] = index;
  }
}


//----------------------------------------------remove part----------------------------------------------
 // removes one horizontal seam in image_. example:
  //
  // image_ before:
  //  0 | 1 | 2 | 3
  // ---+---+---+---
  //  4 | 5 | 6 | 7
  // ---+---+---+---
  //  8 | 9 | 10| 11
  //
  // seam to remove:
  //    | x |   |
  // ---+---+---+---
  //  x |   | x |
  // ---+---+---+---
  //    |   |   | x
  //(1,0,1,2)
  // image_ after:
  //  0 | 5 | 2 | 3
  // ---+---+---+---
  //  8 | 9 | 10| 7
void SeamCarver::RemoveHorizontalSeam() {
  int* data = GetHorizontalSeam();
  auto** newpic = new Pixel*[height_ - 1]; 
  for (int initializerow = 0; initializerow < height_ - 1; ++initializerow) {
    newpic[initializerow] = new Pixel[width_];
  }
  int newrow = 0;
  for (int col = 0; col < width_; ++col) {
    int index = data[col];
    for (int row = 0; row < height_; ++row) {
      if (row == index) {
        continue;
      }
      newpic[newrow][col] = image_.GetPixel(row,col);
      newrow++;
    }
    newrow = 0;
  }
  image_.~ImagePPM();
  image_.SetValue(height_ - 1,width_,image_.GetMaxColorValue(),newpic);
  SetImage(image_);
  delete[] data;
  data = nullptr;
  newpic = nullptr;
}

void SeamCarver::RemoveVerticalSeam() {
  int* data = GetVerticalSeam();
  auto** newpic = new Pixel*[height_];
  for (int initializerow = 0; initializerow < height_; ++initializerow) {
    newpic[initializerow] = new Pixel[width_ - 1];
  }
  for (int row = 0; row < height_; ++row) {
    int index = data[row];
    int newcol = 0;
    for (int col = 0; col < width_; ++col) {
      if (col == index) {
        continue;
      }
      newpic[row][newcol] = image_.GetPixel(row,col);
      newcol++;
    }
    newcol = 0;
  }
  ImagePPM newimage;
  newimage.SetValue(height_,width_ - 1,image_.GetMaxColorValue(),newpic);
  image_.~ImagePPM();
  SetImage(newimage);
  newimage.~ImagePPM();
  delete[] data;
  data = nullptr;
  newpic = nullptr;
}


// given functions below, DO NOT MODIFY

SeamCarver::SeamCarver(const ImagePPM& image): image_(image) {
  height_ = image.GetHeight();
  width_ = image.GetWidth();
}

void SeamCarver::SetImage(const ImagePPM& image) {
  image_ = image;
  width_ = image.GetWidth();
  height_ = image.GetHeight();
}

