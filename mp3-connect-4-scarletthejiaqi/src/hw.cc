#include "hw.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <istream>
#include <stdexcept>
std::vector<int> get_ints_from_file(std::string file_name) {
  std::ifstream ifs(file_name);
  int num;
  std::vector<int> value;
  if (!(ifs.is_open())) {
    throw std::untime_error("not open");
  }
  while(ifs.good()) {
    ifs>>num;
    if (ifs.fail()) {
      ifs.clear();
      ifs.ignore(1);
    } else {
      value.push_back(num);
    }
  }
  return value;
}