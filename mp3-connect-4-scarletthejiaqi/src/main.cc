#include <iostream>
#include<hw.hpp>
#include "board.hpp"
#include <string>
#include <vector>

int main() {
  // Board b;
  std::string name = "/home/vagrant/src/mp3-connect-4-scarletthejiaqi/f";
  std::vector<int> result = get_ints_from_file(name);
  for (int i : result) {
    std::cout<<i<<std::endl;
  }
  
}