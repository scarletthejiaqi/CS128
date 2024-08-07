#ifndef SHARED_POINTER_HPP
#define SHARED_POINTER_HPP

#include <iostream>

enum class kSharedPointerType { kArray, kObject };

template <typename T>
class SharedPointer {
public:
  SharedPointer(T* address,
                kSharedPointerType type = kSharedPointerType::kObject);
  ~SharedPointer();
  SharedPointer(const SharedPointer<T>& source);
  SharedPointer<T>& operator=(const SharedPointer<T>& source);

  // Provided, do not modify!
  SharedPointer() = default;
  T& operator*() { return *holder_; }
  T* operator->() { return holder_; }
  const T* operator->() const { return holder_; }
  T* Get() { return holder_; }
  const T* Get() const { return holder_; }
  unsigned int UseCount() const {
    return (ref_count_ != nullptr) ? *ref_count_ : 0;
  }

private:
  T* holder_ = nullptr;
  kSharedPointerType type_ = kSharedPointerType::kObject;
  unsigned int* ref_count_ = nullptr;
  void Deletehelper();

};

// non-member helper function declarations

// non-member helper function definitions

// member function definitions
template <typename T>
SharedPointer<T>::SharedPointer(T* address, kSharedPointerType type) {
  //deallocate after use??
  holder_ = address;
  //meaning of using karray, do we need to check?
  type_ = type;
  if (address != nullptr) {
    ref_count_ = new unsigned int(1);
  }
}

template <typename T>
SharedPointer<T>::~SharedPointer() {
  if (holder_ == nullptr || ref_count_ == nullptr) {
    return;
  }
  --(*ref_count_);
  Deletehelper();
}

template <typename T>
void SharedPointer<T>::Deletehelper() {
  if ((*ref_count_)==0) {
    if (type_ == kSharedPointerType::kArray) {
      //———————————————————————————————————————————————————— how to deterine how to delete
        delete[] holder_;
      } else {
        delete holder_;
    }
    delete ref_count_;

  }
}

template <typename T>
SharedPointer<T>::SharedPointer(const SharedPointer<T>& source) {
  holder_ = source.holder_;
  type_ = source.type_;
  ref_count_ = source.ref_count_;
  if (source.ref_count_ != nullptr) {
    ++(*ref_count_);
  }
}

template <typename T>
SharedPointer<T>& SharedPointer<T>::operator=(const SharedPointer<T>& source) {
  if (this == &source) {
    return *this;
  }
  if (ref_count_ != nullptr) {
    --(*ref_count_);
    Deletehelper();
  }
  holder_ = source.holder_;
  type_ = source.type_;
  ref_count_ = source.ref_count_;
  if (source.Get() != nullptr) {
    ++(*ref_count_);
  }
  return *this;
}


#endif
