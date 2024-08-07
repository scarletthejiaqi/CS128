#include <iostream>
#include <fstream>
#include "functions.hpp"
#include "utilities.hpp"
#include <vector>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
  std::string dna = argv[2];
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " [input_file] [dna_sequence]"
              << std::endl;
    return 1;
  }

  std::fstream file(argv[1]);

  int index0 = 0;
  std::vector<std::string>  first_vector;
  std::vector<std::string> match;
  for (std::string line; std::getline(file,line); line="") {
    std::vector<std::string>  each_vector  = utilities::GetSubstrs(line,',');
    if (index0 == 0) {
      first_vector = utilities::GetSubstrs(line,',');
      index0++;
    } else {
      std::vector<std::string> person = utilities::GetSubstrs(line,',');
      if (FindPerson(first_vector,dna,person) == 1) {
        match.push_back(each_vector.at(0));
      }
    }
  }

  if (match.size()!= 1) {
    std::cout<<"No match"<<std::endl;
  } else {
    std::cout<<match.at(0)<<std::endl;
  }
  return 0;
}