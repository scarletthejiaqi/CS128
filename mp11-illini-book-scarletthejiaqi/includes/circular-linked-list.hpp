#ifndef CIRCULAR_LINKED_LIST_HPP
#define CIRCULAR_LINKED_LIST_HPP

#include <iostream>

#include "node.hpp"

enum class Order { kASC, kDESC };

template <typename T>
class CircularLinkedList {
public:
  CircularLinkedList() = default;
  CircularLinkedList(CircularLinkedList<T>&& source);
  CircularLinkedList<T>& operator=(CircularLinkedList<T>&& source);
  ~CircularLinkedList();
  void push_back(const T& data);
  T& front();
  T& back();
  void set_order(Order order);


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

template <typename T>
CircularLinkedList<T>::~CircularLinkedList() {
  if (head_ == nullptr) return;

  // non-empty list condition
  Node<T>* original_head = head_;
  Node<T>* next = nullptr;
  do {
    next = head_->next;
    delete head_;
    head_ = next;
  } while (head_ != original_head);
}

template <typename T>
CircularLinkedList<T>::CircularLinkedList(CircularLinkedList<T>&& source)
    : head_(nullptr),tail_(nullptr),node_order_(source.node_order_) {
  if (source.head_ == nullptr) {
    return;
  }
  head_ = std::move(source.head_);
  tail_ = std::move(source.tail_);
  
//   // delete source
//   Node<T>* original_head = source.head_;
//   Node<T>* next = nullptr;
//   do {
//     next = source.head_->next;
//     delete source.head_;
//     source.head_ = next;
//   } while (source.head_ != original_head);

    source.head_ = nullptr;
    source.tail_ = nullptr;
}

template <typename T>
CircularLinkedList<T>& CircularLinkedList<T>::operator=(CircularLinkedList<T>&& source) {
  if (this == &source) {
    return *this;
  }
  // delete original
  Node<T>* original_head = head_;
  Node<T>* next = nullptr;
  do {
    next = head_->next;
    delete head_;
    head_ = next;
  } while (head_ != original_head);

  head_ = std::move(source.head_);
  tail_ = std::move(source.tail_);
  node_order_ = std::move(source.node_order_);

//   if (source.head_ == nullptr) {
//     return *this;
//   }

    source.head_ = nullptr;
    source.tail_ = nullptr;
  return *this;
}

//test
template <typename T>
void CircularLinkedList<T>::push_back(const T& data) {
  Node<T>* new_node = new Node<T>{data};
  if (head_ == nullptr) {
    head_ = new_node;
    tail_ = new_node;
  } else {
    tail_->next = new_node;
    tail_ = new_node;
  }
  tail_->next = head_;
}

template <typename T>
T& CircularLinkedList<T>::front() {
  if (head_ == nullptr) {
    throw std::out_of_range("List is empty");
  }
  return head_->data;
}

template <typename T>
T& CircularLinkedList<T>::back() {
  if (tail_ == nullptr) {
    throw std::out_of_range("List is empty");
  }
  return tail_->data;
}

template <typename T>
void CircularLinkedList<T>::set_order(Order order) {

  node_order_ = order;
}

#endif
