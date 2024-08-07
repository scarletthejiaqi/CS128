#include "color.hpp"
#include <stdexcept>
#include <iostream>

Color::Color(int r, int g, int b): red_(r), green_(g), blue_(b) {
  if (r > kColorValueMax || r < 0 || g > kColorValueMax || g < 0 || b > kColorValueMax || b < 0) {
    // std::cout<<"r"<<r<<"g"<<g<<"b"<<b<<std::endl;
    throw std::runtime_error("color out of bound");
  }
  // need to ensure valid color has been constructed...
}

// do not modify
bool operator==(const Color& rhs, const Color& lhs) {
  return (rhs.Red() == lhs.Red() && rhs.Green() == lhs.Green() &&
          rhs.Blue() == lhs.Blue());
}