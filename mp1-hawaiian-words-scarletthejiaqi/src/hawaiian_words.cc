#include <iostream>
#include <string>
#include <cctype>
#include "functions.hpp"

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Usage: ./bin/exec word" << std::endl;
    return 1;
  }
  std::string word = argv[1];
  std::string lower_word;
  std::string substring;
  for (char i : word) {
    lower_word += std::tolower(i);
  }
  std::string phonetics;
  std::string rest = lower_word;
  for (unsigned int i = 0; i < lower_word.size(); ++i) {
    char next = ' ';
    char prev = ' ';
    char current = lower_word.at(i);
    if (current != 'a' && current != 'e' && current != 'i' && current != 'o' && current != 'u' && current != 'p' && current != 'k' && current != 'l' && current != 'm' && current != 'n' && current != 'w' && current != 'h' && current != ' ' && current != '\'') {
      std::cout << word << " contains a character not a part of the Hawaiian language." << std::endl;
      return 0;
    }
    if (i < lower_word.size() - 1) {
      next = lower_word.at(i+1);
    }
    if (i > 0) {
      prev = lower_word.at(i-1);
    }
    if (i > 1) {
      substring = lower_word.substr(i-2,i-1);
    }
    phonetics = Cases (prev, substring, next, phonetics, current);
  }
  phonetics = EndsWith(phonetics);
  std::cout << phonetics << std::endl;
  return 0;
}