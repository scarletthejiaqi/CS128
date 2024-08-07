#include "cord.hpp"

#include <stdexcept>
#include "cord_utilities.hpp"

// create new leaf cord which data has char array
Cord::Cord(std::string_view sv) {
  if (sv.empty()) {
    throw std::invalid_argument("empty sv");
  }
  length_ = sv.size();
  data_ = new char[sv.size() + 1];
  for (unsigned int i = 0; i < sv.size(); ++i) {
    data_[i] = sv.at(i);
  }
  data_[sv.size()] = '\0';
}
Cord::~Cord() {
  // free uniquely owned by this cord?
  delete[] data_;
}

// create a shared pointer which points to the data of this cord(ref++)
SharedPointer<char> Cord::ToString() const {
  if (data_ != nullptr) {
    char* output = new char[length_ + 1];
    for (unsigned int i = 0; i < length_; ++i) {
      output[i] = data_[i];
    }
    output[length_] = '\0';
    return SharedPointer{output, kSharedPointerType::kArray};
  }
  char* newdata = new char[length_ + 1];
  std::stack<std::string_view> stack;
  Createstack(right_,stack);
  Createstack(left_,stack);
  Insertvalue(stack,newdata);
  return SharedPointer{newdata,kSharedPointerType::kArray};
}

void Cord::Createstack(SharedPointer<Cord> pointer, std::stack<std::string_view>& stack) const {
    if (pointer.Get() != nullptr) {
        Createstack(pointer->Right(),stack);
        Createstack(pointer->Left(),stack);
        if (pointer.Get()->Left().Get() == nullptr && pointer.Get()->Right().Get() == nullptr) {
            stack.push(pointer.Get()->Data());
        }
    }
}

void Cord::Insertvalue(std::stack<std::string_view>& stack, char*& newdata) const{
  unsigned int index = 0;
  while (!stack.empty()) {
    for (unsigned int i = 0; i < stack.top().size(); ++i) {
      newdata[index + i] = stack.top().at(i);
    }
    index += stack.top().size();
    stack.pop();
  }
  newdata[length_] = '\0';
}

