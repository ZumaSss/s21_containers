#ifndef SRC_CORE_S21_VECTOR_H_
#define SRC_CORE_S21_VECTOR_H_

#include <algorithm>
#include <limits>

#include "s21_container.h"

namespace s21 {

template <typename T>
class vector : public IContainer {
  // Types
 public:
  class VectorIterator;
  class VectorConstIterator;

  using typename IContainer::size_type;
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = vector<value_type>::VectorIterator;
  using const_iterator = vector<value_type>::VectorConstIterator;

  // Public Methods
 public:
  vector() noexcept;
  vector(size_type n);
  vector(std::initializer_list<value_type> const& items);
  vector(const vector& other);
  vector(vector&& other) noexcept;
  ~vector();

  vector<value_type>& operator=(const vector<value_type>& other);
  vector<value_type>& operator=(vector<value_type>&& other);

  static size_type max_size();

  size_type capacity() const noexcept;
  virtual size_type size() const noexcept override;
  virtual bool empty() const noexcept override;
  void clear();

  value_type* data() const noexcept;

  iterator begin();
  const_iterator begin() const;

  iterator end();
  const_iterator end() const;

  reference at(size_type pos);
  const_reference at(size_type pos) const;

  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;

  const_reference front() const;
  const_reference back() const;

  void reserve(size_type size);
  void shrink_to_fit();

  void swap(vector<value_type>& other) noexcept;
  iterator insert(iterator pos, const_reference value);
  void push_back(const_reference value);
  void pop_back();
  void erase(iterator pos);

  template <typename... Args>
  void insert_many_back(Args&&... args);

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);

  bool operator==(const vector<value_type>& other) const;
  bool operator!=(const vector<value_type>& other) const;

  // Data
 private:
  size_type size_;
  size_type capacity_;
  value_type* data_;

  // Private Methods
 private:
  void moveValData(size_type indx, value_type&& val);
  void freeValData(size_type indx);

  void makeData();
  void freeData();

  void setCapacity(size_type newCapacity);
  void growCapacity();

  void checkRange(const_iterator begin, const_iterator pos) const;

  iterator insertImpl(iterator pos, const_reference value);
};

template <typename T>
class vector<T>::VectorIterator {
  // Types
 public:
  using iterator_category = std::random_access_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using value_type = T;
  using pointer = T*;
  using reference = T&;
  using const_reference = const T&;

  // Public Methods
 public:
  VectorIterator(value_type* ptr) : ptr_(ptr) {}
  VectorIterator(VectorIterator& other) : ptr_(other.ptr_) {}

  VectorIterator& operator++() {
    ++ptr_;
    return *this;
  }

  VectorIterator operator++(int) {
    VectorIterator temp = *this;
    ++ptr_;
    return temp;
  }

  VectorIterator operator+(int shift) {
    VectorIterator temp = *this;
    temp.ptr_ += shift;
    return temp;
  }

  VectorIterator operator+(const VectorIterator& shift) {
    VectorIterator temp = *this;
    temp.ptr_ += shift.ptr_;
    return temp;
  }

  VectorIterator& operator--() {
    --ptr_;
    return *this;
  }

  VectorIterator operator--(int) {
    VectorIterator temp = *this;
    --ptr_;
    return temp;
  }

  VectorIterator operator-(int shift) {
    VectorIterator temp = *this;
    temp.ptr_ -= shift;
    return temp;
  }

  VectorIterator operator-(const VectorIterator& shift) {
    VectorIterator temp = *this;
    temp.ptr_ -= shift.ptr_;
    return temp;
  }

  bool operator==(const VectorIterator& other) const {
    return (ptr_ == other.ptr_);
  }

  bool operator!=(const VectorIterator& other) const {
    return !(*this == other);
  }

  reference operator*() const { return *ptr_; }

  static difference_type distance(const VectorIterator& first,
                                  const VectorIterator& second) {
    return std::distance(first.ptr_, second.ptr_);
  }

  // Data
 private:
  value_type* ptr_;
};

template <typename T>
class vector<T>::VectorConstIterator : public vector<T>::VectorIterator {
  // Types
 public:
  using iterator_category = std::random_access_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using value_type = T;
  using pointer = T*;
  using reference = T&;
  using const_reference = const T&;

 public:
  VectorConstIterator(VectorIterator other) : VectorIterator(other) {}
  const_reference operator*() { return VectorIterator::operator*(); }
};

template <typename value_type>
vector<value_type>::vector() noexcept
    : size_{0}, capacity_{0}, data_{nullptr} {}

template <typename value_type>
vector<value_type>::vector(size_type n)
    : size_{n}, capacity_{n}, data_{nullptr} {
  if (capacity_ > max_size())
    throw std::length_error("Cannot create s21::vector larger than max_size()");

  makeData();

  for (size_type i = 0; i < size_; i++) {
    new (data_ + i) value_type();
  }
}

template <typename value_type>
vector<value_type>::vector(std::initializer_list<value_type> const& items)
    : size_{items.size()}, capacity_{items.size()}, data_{nullptr} {
  if (capacity_ > max_size())
    throw std::length_error("Cannot create s21::vector larger than max_size()");

  makeData();

  size_type i = 0;
  for (auto item : items) {
    new (data_ + i) value_type(item);
    i++;
  }
}

template <typename value_type>
vector<value_type>::vector(const vector& other)
    : size_{other.size_}, capacity_{other.capacity_}, data_{nullptr} {
  makeData();

  for (size_type i = 0; i < size_; i++) {
    new (data_ + i) value_type(other[i]);
  }
}

template <typename value_type>
vector<value_type>::vector(vector&& other) noexcept
    : size_{other.size_}, capacity_{other.capacity_}, data_{other.data_} {
  if (this != &other) {
    other.size_ = 0;
    other.capacity_ = 0;
    other.data_ = nullptr;
  }
}

template <typename value_type>
vector<value_type>::~vector() {
  freeData();
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::begin() {
  return iterator(&data_[0]);
};

template <typename value_type>
typename vector<value_type>::const_iterator vector<value_type>::begin() const {
  return const_iterator(&data_[0]);
};

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::end() {
  return iterator(&data_[size_]);
};

template <typename value_type>
typename vector<value_type>::const_iterator vector<value_type>::end() const {
  return const_iterator(&data_[size_]);
};

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::size()
    const noexcept {
  return size_;
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::max_size() {
  return ((std::numeric_limits<size_type>::max() / sizeof(value_type)) /
          4294967296);  // #NOTE: 4294967296 -> 2^32
}

template <typename value_type>
bool vector<value_type>::empty() const noexcept {
  return (size_ == 0);
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::capacity()
    const noexcept {
  return capacity_;
}

template <typename value_type>
value_type* vector<value_type>::data() const noexcept {
  return data_;
}

template <typename value_type>
typename vector<value_type>::reference vector<value_type>::at(size_type pos) {
  if (pos >= size_) throw std::out_of_range("Index out of vector boundary");

  return data_[pos];
}

template <typename value_type>
typename vector<value_type>::const_reference vector<value_type>::at(
    size_type pos) const {
  if (pos >= size_) throw std::out_of_range("Index out of vector boundary");

  return data_[pos];
}

template <typename value_type>
typename vector<value_type>::reference vector<value_type>::operator[](
    size_type pos) {
  return data_[pos];
}

template <typename value_type>
typename vector<value_type>::const_reference vector<value_type>::operator[](
    size_type pos) const {
  return data_[pos];
}

template <typename value_type>
void vector<value_type>::moveValData(size_type indx, value_type&& val) {
  new (data_ + indx) value_type(std::move(val));
}

template <typename value_type>
void vector<value_type>::freeValData(size_type indx) {
  if (data_ != nullptr) (data_ + indx)->~value_type();
}

template <typename value_type>
void vector<value_type>::makeData() {
  value_type* newData = reinterpret_cast<value_type*>(
      new std::byte[capacity_ * sizeof(value_type)]);
  if (data_ != nullptr) {
    for (size_type i = 0; i < size_; i++) {
      try {
        new (newData + i) value_type(std::move(data_[i]));
      } catch (...) {
        for (size_type j = 0; j < i; j++) {
          (newData + i)->~value_type();
        }
        delete[] reinterpret_cast<std::byte*>(newData);
        throw;
      }
    }

    freeData();
  }

  data_ = newData;
}

template <typename value_type>
void vector<value_type>::freeData() {
  if (data_ == nullptr) return;

  for (size_type i = 0; i < size_; i++) {
    freeValData(i);
  }

  delete[] reinterpret_cast<uint8_t*>(data_);
}

template <typename value_type>
void vector<value_type>::setCapacity(size_type newCapacity) {
  capacity_ = newCapacity;
  if (capacity_ > max_size())
    throw std::length_error("Cannot expand s21::vector larger than max_size()");

  makeData();
}

template <typename value_type>
void vector<value_type>::growCapacity() {
  if (capacity_ == 0) {
    reserve(1);
  } else {
    reserve(capacity_ * 2);
  }
}

template <typename value_type>
void vector<value_type>::reserve(size_type newCapacity) {
  if (newCapacity <= capacity_) return;
  setCapacity(newCapacity);
}

template <typename value_type>
void vector<value_type>::shrink_to_fit() {
  if (size_ == capacity_) return;
  setCapacity(size_);
}

template <typename value_type>
void vector<value_type>::clear() {
  for (size_type i = 0; i < size_; i++) {
    (data_ + i)->~value_type();
  }

  size_ = 0;
}

template <typename value_type>
void vector<value_type>::swap(vector<value_type>& other) noexcept {
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
  std::swap(data_, other.data_);
}

template <typename value_type>
bool vector<value_type>::operator==(const vector<value_type>& other) const {
  if (this == &other) return true;
  if (size() != other.size()) return false;

  return (std::equal(begin(), end(), other.begin()));
}

template <typename value_type>
bool vector<value_type>::operator!=(const vector<value_type>& other) const {
  return !(*this == other);
}

template <typename value_type>
vector<value_type>& vector<value_type>::operator=(
    const vector<value_type>& other) {
  if (this == &other) {
    return *this;
  }

  vector<value_type> tmp{other};
  this->swap(tmp);

  return *this;
}

template <typename value_type>
vector<value_type>& vector<value_type>::operator=(vector<value_type>&& other) {
  if (this == &other) {
    return *this;
  }

  vector<value_type> tmp{std::move(other)};
  this->swap(tmp);

  return *this;
}

template <typename value_type>
typename vector<value_type>::const_reference vector<value_type>::front() const {
  return data_[0];
}

template <typename value_type>
typename vector<value_type>::const_reference vector<value_type>::back() const {
  return data_[size_ - 1];
}

template <typename value_type>
void vector<value_type>::push_back(const_reference value) {
  if (size_ >= capacity_) growCapacity();

  value_type tmp{value};
  moveValData(size_, std::move(tmp));

  ++size_;
}

template <typename value_type>
void vector<value_type>::pop_back() {
  if (empty()) throw std::out_of_range("Vector is empty");
  --size_;

  freeValData(size_);
}

template <typename value_type>
void vector<value_type>::erase(iterator pos) {
  const auto index = (size_type)VectorIterator::distance(begin(), pos);
  if (index >= size_) return;

  freeValData(index);

  for (size_type i = index; i < (size_ - 1); i++) {
    moveValData(i, std::move(data_[i + 1]));
  }

  --size_;
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::insertImpl(
    iterator pos, const_reference value) {
  const auto index = (size_type)VectorIterator::distance(begin(), pos);
  if (size_ >= capacity_) growCapacity();

  for (size_type i = size_; i > index; i--) {
    moveValData(i, std::move(data_[i - 1]));
  }

  // #DEFECT - how to correct move value to data without tmp?
  value_type tmp{value};
  moveValData(index, std::move(tmp));
  ++size_;

  return begin() + index;
}

template <typename value_type>
void vector<value_type>::checkRange(const_iterator begin,
                                    const_iterator pos) const {
  const auto index = (size_type)VectorIterator::distance(begin, pos);
  if ((index >= size_) && (index != 0))
    throw std::out_of_range("Selected position is out of range of the vector");
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::insert(
    iterator pos, const_reference value) {
  checkRange(begin(), pos);

  return insertImpl(pos, value);
}

template <typename value_type>
template <typename... Args>
void vector<value_type>::insert_many_back(Args&&... args) {
  for (auto arg : {args...}) {
    push_back(arg);
  }
}

template <typename value_type>
template <typename... Args>
typename vector<value_type>::iterator vector<value_type>::insert_many(
    const_iterator pos, Args&&... args) {
  checkRange(begin(), pos);

  for (auto arg : {args...}) {
    pos = insertImpl(pos, arg) + 1;
  }

  return pos;
}

}  // namespace s21

#endif  // SRC_CORE_S21_VECTOR_H_