#ifndef SRC_CORE_S21_STACK_H_
#define SRC_CORE_S21_STACK_H_

#include "s21_container.h"
#include "s21_list.h"

namespace s21 {
template <typename T>
class stack {
 public:
  using size_type = std::size_t;
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;

  stack() noexcept {};
  stack(const std::initializer_list<value_type>& items);
  stack(const stack& other);
  stack(stack&& other);
  ~stack(){};

  bool empty() noexcept;
  size_type size() noexcept;

  void push(const_reference value);
  void pop();
  const_reference top();
  void swap(stack& other);

  stack& operator=(stack&& other);

  template <class... Args>
  void insert_many_front(Args&&... args);

 private:
  s21::list<value_type> data_;
};

template <typename value_type>
stack<value_type>::stack(const std::initializer_list<value_type>& items)
    : data_{items} {}

template <typename value_type>
stack<value_type>::stack(const stack& other) : data_{other.data_} {}

template <typename value_type>
stack<value_type>::stack(stack&& other) : data_{std::move(other.data_)} {}

template <typename value_type>
bool stack<value_type>::empty() noexcept {
  return data_.empty();
}

template <typename value_type>
typename stack<value_type>::size_type stack<value_type>::size() noexcept {
  return data_.size();
}

template <typename value_type>
void stack<value_type>::push(const_reference value) {
  data_.push_back(value);
}

template <typename value_type>
void stack<value_type>::pop() {
  data_.pop_back();
}

template <typename value_type>
typename stack<value_type>::const_reference stack<value_type>::top() {
  return data_.back();
}

template <typename value_type>
void stack<value_type>::swap(stack& other) {
  std::swap(data_, other.data_);
}

template <typename value_type>
stack<value_type>& stack<value_type>::operator=(stack&& other) {
  if (this == &other) {
    return *this;
  }
  this->swap(other);
  return *this;
}

template <typename value_type>
template <class... Args>
void stack<value_type>::insert_many_front(Args&&... args) {
  for (auto arg : {args...}) {
    this->push(arg);
  }
}
}  // namespace s21

#endif  // SRC_CORE_S21_STACK_H_