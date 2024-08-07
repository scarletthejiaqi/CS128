#include <iostream>

#include "cord_utilities.hpp"
#include "cord.hpp"

int main() {
  SharedPointer<Cord> a = new Cord("CS");
  SharedPointer<Cord> b = new Cord("12");
  SharedPointer<Cord> c = ConcatCords(a, b);
  SharedPointer<Cord> d = new Cord("Sc");
  SharedPointer<Cord> e = ConcatCords(c, d);

  SharedPointer<Cord> a1 = new Cord("an");
  SharedPointer<Cord> b1 = new Cord("wh");
  SharedPointer<Cord> c1 = ConcatCords(a1, b1);
  SharedPointer<Cord> d1 = new Cord("id");
  SharedPointer<Cord> e1 = ConcatCords(c1, d1);

  SharedPointer<Cord> highest = ConcatCords(e, e1);
  // auto a_str = a->ToString();

  // auto c_str = c->ToString();
  // std::cout << c_str.Get() << std::endl;

  auto res = SubString(highest, 6, 120);
  auto res_str = res->ToString();
  std::cout << res_str.Get() << std::endl;
}