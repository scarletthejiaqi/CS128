// #include "illini_book.hpp"
#include <iostream>
// int main() {
//   IlliniBook ib("/home/vagrant/src/mp11-illini-book-scarletthejiaqi/example/persons.csv", "/home/vagrant/src/mp11-illini-book-scarletthejiaqi/example/relations.csv");
  
//   std::cout<<ib.GetRelated(3, 2)<<std::endl;
//   std::cout<<ib.GetRelated(1, 2)<<std::endl;
//   std::cout<<ib.GetRelated(1, 9)<<std::endl;
//   std::cout<<ib.GetRelated(1, 2, "128")<<std::endl;
//   std::cout<<ib.GetRelated(1, 2, "124")<<std::endl;
//   std::cout<<ib.GetRelated(1, 6, "128")<<std::endl;
//   std::cout<<ib.GetSteps(1, 2)[1]<<std::endl;
//   std::cout<<ib.GetSteps(1, 3).empty()<<std::endl;
//   std::cout<<ib.CountGroups()<<std::endl;
//   std::cout<<ib.CountGroups(std::vector<std::string>{ "128"});
//   // std::cout<<ib.CountGroups(std::vector<std::string>{ "128", "124", "173" })<<std::endl;
// if (ib.AreRelated(1,2,"128")) {
//     std::cout<<"yes"<<std::endl;
//   }
//   for (int i : ib.GetSteps(1, 1)) {
//     std::cout<<i<<std::endl;
//   }
// }

// #include "circular-linked-list.hpp"
// #include <cassert>
// #include <sstream>
// int main() {
// // create a new circular linked list
//   CircularLinkedList<int> cll;
//   CircularLinkedList<int> cll3;
//   CircularLinkedList<int> nothing;
//   cll.set_order(Order::kDESC);
//   // add some elements to the list
//   cll.push_back(1);
//   cll.push_back(2);
//   cll.push_back(3);
//   cll3.push_back(1);
  
//   // print the original list
//   std::cout << "Original list: " << cll << std::endl;
  
//   // move construct a new list from the original
//   CircularLinkedList<int> cll2(std::move(cll));
  
//   // print the new list
//   std::cout << "Moved list: " << cll2 << std::endl;

//   cll3 = std::move(cll2);
//   std::cout << "equal list: " << cll3 << std::endl;
//   return 0;
// }

