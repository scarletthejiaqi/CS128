#include <iostream>
#include <string>
#include <vector>
#include <vector>
#include "WordSearchSolver.hpp"

int main() {
//   std::vector<std::vector<char>> puzzle{{'h', 'e', 'a', 'o', 'u'},
//                                         {'e', 'e', 'l', 'l', 'o'},
//                                         {'l', 'a', 'l', 'o', 'm'},
//                                         {'l', 'e', 't', 'o', 'u'},
//                                         {'o', 'e', 't', 'o', 'u'}};
// WordSearchSolver wss(puzzle);
// std::cout << wss.FindWord("helouu", CheckDirection::kVertical);
// std::cout << wss.FindWord("hello");
// std::cout<<wss.FindWord("hello",CheckDirection::kVertical);
std::string name = "/home/vagrant/src/mp3-connect-4-scarletthejiaqi/f";
  std::vector<int> result = get_ints_from_file(name);
  for (int i : result) {
    std::cout<<i<<std::endl;
  }
}