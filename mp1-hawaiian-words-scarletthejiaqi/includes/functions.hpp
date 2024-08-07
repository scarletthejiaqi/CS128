#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include <iostream>
#include <string>

// Your function declarations should go in this header file.
std::string DealW(char c, std::string s);
std::string DealA(char c, std::string s);
std::string DealE(char prev, std::string s, char nex);
std::string DealI(char prev, std::string s,char nex, const std::string &substring);
std::string DealO(char prev, std::string s, char nex);
std::string DealU(char prev, std::string s, char nex);
std::string EndsWith(std::string s);
std::string Cases (char prev, std::string substring, char next, std::string phonetics, char current);
#endif