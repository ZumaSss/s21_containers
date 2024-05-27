#ifndef SRC_CORE_S21_ARRAY_H_
#define SRC_CORE_S21_ARRAY_H_

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <utility>

#include "s21_container.h"

namespace s21 {

template <typename T, std::size_t N>
class array : IContainer {
  // Types
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using typename IContainer::size_type;

  // Public Methods
 public:
  array() = default;
  array(const std::initializer_list<value_type> &items);
  array(const array &other);
  array(array &&other) noexcept;
  ~array(){};

  array &operator=(const array &other);
  array &operator=(array &&other) noexcept;

  iterator begin() noexcept { return data_; }
  const_iterator begin() const noexcept { return data_; }
  iterator end() noexcept { return data_ + N; }
  const_iterator end() const noexcept { return data_ + N; }

  const_reference front() const noexcept { return data_[0]; }
  const_reference back() const noexcept { return data_[(N == 0) ? 0 : N - 1]; }

  reference at(size_type pos);
  const_reference at(size_type pos) const;

  reference operator[](size_type pos) noexcept { return data_[pos]; }
  const_reference operator[](size_type pos) const noexcept {
    return data_[pos];
  }

  iterator data() noexcept { return data_; }
  const_iterator data() const noexcept { return data_; }

  static size_type max_size() noexcept;
  virtual size_type size() const noexcept override { return N; }
  virtual bool empty() const noexcept override { return (N == 0); }

  void swap(array &other) noexcept { std::swap(data_, other.data_); }
  void fill(const_reference value) { std::fill(begin(), end(), value); }

  // Data
 private:
  value_type data_[N];
};

template <typename value_type, std::size_t N>
array<value_type, N>::array(const std::initializer_list<value_type> &items) {
  if (items.size() > max_size())
    throw std::length_error("Cannot create s21::array larger than max_size()");
  if (items.size() > N)
    throw std::length_error("Too many initializers for s21::array");

  std::copy(items.begin(), items.end(), data_);
}

template <typename value_type, std::size_t N>
array<value_type, N>::array(const array &other) {
  std::copy(other.begin(), other.end(), data_);
}

template <typename value_type, std::size_t N>
array<value_type, N>::array(array &&other) noexcept {
  std::move(other.begin(), other.end(), data_);
}

template <typename value_type, std::size_t N>
array<value_type, N> &array<value_type, N>::operator=(const array &other) {
  if (this != &other) {
    std::copy(other.begin(), other.end(), data_);
  }

  return *this;
}

template <typename value_type, std::size_t N>
array<value_type, N> &array<value_type, N>::operator=(array &&other) noexcept {
  if (this != &other) {
    std::move(other.begin(), other.end(), data_);
  }

  return *this;
}

template <typename value_type, std::size_t N>
typename array<value_type, N>::size_type
array<value_type, N>::max_size() noexcept {
  return ((std::numeric_limits<size_type>::max() / sizeof(value_type)) /
          4294967296);  // #NOTE: 4294967296 -> 2^32
}

template <typename value_type, std::size_t N>
typename array<value_type, N>::reference array<value_type, N>::at(
    size_type pos) {
  if (pos >= N) throw std::out_of_range("Index out of array boundary");

  return data_[pos];
}

template <typename value_type, std::size_t N>
typename array<value_type, N>::const_reference array<value_type, N>::at(
    size_type pos) const {
  if (pos >= N) throw std::out_of_range("Index out of array boundary");

  return data_[pos];
}

}  // namespace s21

#endif  // SRC_CORE_S21_ARRAY_H_