#ifndef CIRCULAR_LINKED_LIST_HPP
#define CIRCULAR_LINKED_LIST_HPP

#include <iostream>

#include "node.hpp"


enum class Order { kASC, kDESC };

template <typename T>
class CircularLinkedList {
public:
  CircularLinkedList() = default;
  CircularLinkedList(const CircularLinkedList<T>& source);
  CircularLinkedList<T>& operator=(const CircularLinkedList<T>& source);
  ~CircularLinkedList();

  void InsertInOrder(const T& data);
  void Reverse();

  void Deletehelper();
  void Ascending(const T& data);
  void Dscending(const T& data);


  template <typename U>
  friend std::ostream& operator<<(std::ostream& os,
                                  const CircularLinkedList<U>& cll);

private:
  Node<T>* head_ = nullptr;
  Node<T>* tail_ = nullptr;
  Order node_order_ = Order::kASC;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const CircularLinkedList<T>& cll) {
  Node<T>* iter = cll.head_;
  // empty list condition
  if (iter == nullptr) {
    os << "Empty list";
    return os;
  }
  // non-empty list condition
  do {
    os << iter->data << '\t';
    iter = iter->next;
  } while (iter != cll.head_);

  return os;
}


template<typename T>
CircularLinkedList<T>::CircularLinkedList(const CircularLinkedList<T>& source): node_order_(source.node_order_) {
  if (source.head_ == nullptr && source.tail_ == nullptr) {
    return;
  }
  head_ = new Node<T>(source.head_->data);
  head_->next = head_;
  Node<T>* current = source.head_;
  Node<T>* newcurr = head_;
  int count = 0;
  while (current -> next != nullptr) {
    count++;
    current = current -> next;
    if (current == source.head_) {
      newcurr->next = head_;
      tail_ = newcurr;
      return;
    }
    auto* newnode = new Node<T>(current->data);
    newcurr->next = newnode;
    newcurr = newnode;
    
  }
}

template<typename T>
CircularLinkedList<T>& CircularLinkedList<T>::operator=(const CircularLinkedList<T>& source) {
  if (this == &source) {
    return *this;
  }
  Deletehelper();
  node_order_ = source.node_order_;
  if (source.head_ == nullptr && source.tail_ == nullptr) {
    return *this;
  }
  head_ = new Node<T>(source.head_->data);
  head_->next = head_;
  Node<T>* current = source.head_;
  Node<T>* newcurr = head_;
  int count = 0;
  while (current -> next != nullptr) {
    count++;
    current = current -> next;
    if (current == source.head_) {
      newcurr->next = head_;
      tail_ = newcurr;
      return *this;
    }
    auto* newnode = new Node<T>(current->data);
    newcurr->next = newnode;
    newcurr = newnode;
  }
  return *this;
}

template<typename T>
void CircularLinkedList<T>::Deletehelper() {
  Node<T>* curr = head_;
  Node<T>* temp = nullptr;
  while (temp!= head_) {
    temp = curr->next;
    delete curr;
    curr = temp;
  }
}

template<typename T>
CircularLinkedList<T>::~CircularLinkedList() {
  Deletehelper();
}

template<typename T>
void CircularLinkedList<T>::InsertInOrder(const T& data) {
  if (head_ == nullptr) {
    head_ = new Node<T>(data);
    head_->next = head_;
    tail_ = head_;
    return;
  }
  if (node_order_ == Order::kASC) {
    //ascending
    Ascending(data);
  } else {
    //descending
    Dscending(data);
  }
}
template <typename T>
void CircularLinkedList<T>::Ascending(const T& data)  {
  Node<T>* curr = head_;
  Node<T>* prev = tail_;
  int count = 0;
  auto* insert = new Node<T>(data);
  if(tail_->data == curr->data) {
      tail_->next = insert;
      insert->next = head_;
    if (data>tail_->data) {
      tail_ = insert;
    } else {
      head_ = insert;
    }
    return;
  }
  while (data>curr->data) {
    count++;
    prev = curr;
    curr = curr->next;
    if(count!= 0 && prev==tail_) {
      break;
    }
  }
  if(count == 0) {
    //smallest
    insert->next = head_;
    tail_->next = insert;
    head_ = insert;
  } else if (prev==tail_) {
    //largest
    tail_->next = insert;
    insert->next = head_;
    tail_ = insert;
  } else {
    //middle
    prev->next = insert;
    insert->next = curr;
  }
}

template <typename T>
void CircularLinkedList<T>::Dscending(const T& data)  {
  Node<T>* curr = head_;
  Node<T>* prev = tail_;
  int count = 0;
  auto* insert = new Node<T>(data);
  if(tail_->data == curr->data) {
      tail_->next = insert;
      insert->next = head_;
    if (data<tail_->data) {
      tail_ = insert;
    } else {
      head_ = insert;
    }
    return;
  }
  while (data<curr->data) {
    count++;
    prev = curr;
    curr = curr->next;
    if(count!= 0 && prev==tail_) {
      break;
    }
  }
  if(count == 0) {
    //largest
    insert->next = head_;
    tail_->next = insert;
    head_ = insert;
  } else if (prev==tail_) {
    //smallest
    tail_->next = insert;
    insert->next = head_;
    tail_ = insert;
  } else {
    //middle
    prev->next = insert;
    insert->next = curr;
  }
}
template<typename T>
void CircularLinkedList<T>::Reverse() {
  if (node_order_ == Order::kASC) {
    node_order_ = Order::kDESC;
  } else {
    node_order_ = Order::kASC;
  }
  if (head_ == nullptr && tail_ == nullptr) {
    return;
  }
  Node<T>* prev = head_;
  Node<T>* curr = head_->next;
  Node<T>* future = curr->next;
  while (curr != head_) {
    curr->next = prev;
    prev = curr;
    curr = future;
    future = future->next;
  }//a round over except not changing head_
  head_->next = tail_;
  head_ = prev;
  tail_ = curr;
}

#endif