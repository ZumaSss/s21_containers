#ifndef SRC_CORE_S21_QUEUE_H_
#define SRC_CORE_S21_QUEUE_H_

#include "s21_container.h"
#include "s21_list.h"

namespace s21 {
template <typename T>
class queue : public IContainer {
  // Types
 public:
  using typename IContainer::size_type;
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;

  // Public Methods
 public:
  queue() noexcept {};
  queue(std::initializer_list<value_type> const& items);
  queue(const queue& other);
  queue(queue&& other) noexcept;
  ~queue(){};

  queue<value_type>& operator=(const queue<value_type>& other);
  queue<value_type>& operator=(queue<value_type>&& other);

  static size_type max_size();
  virtual size_type size() const noexcept override;
  virtual bool empty() const noexcept override;

  const_reference front() const;
  const_reference back() const;

  void swap(queue<value_type>& other) noexcept;
  void push(const_reference value);
  void pop();

  template <typename... Args>
  void insert_many_back(Args&&... args);

  // Data
 private:
  s21::list<T> data_;
};

template <typename value_type>
queue<value_type>::queue(std::initializer_list<value_type> const& items)
    : data_{items} {}

template <typename value_type>
queue<value_type>::queue(const queue& other) : data_{other.data_} {}

template <typename value_type>
queue<value_type>::queue(queue&& other) noexcept
    : data_{std::move(other.data_)} {}

template <typename value_type>
typename queue<value_type>::size_type queue<value_type>::size() const noexcept {
  return data_.size();
}

template <typename value_type>
typename queue<value_type>::size_type queue<value_type>::max_size() {
  return list<value_type>::max_size();
}

template <typename value_type>
bool queue<value_type>::empty() const noexcept {
  return data_.empty();
}

template <typename value_type>
void queue<value_type>::swap(queue<value_type>& other) noexcept {
  data_.swap(other.data_);
}

template <typename value_type>
queue<value_type>& queue<value_type>::operator=(
    const queue<value_type>& other) {
  if (this == &other) {
    return *this;
  }

  queue<value_type> tmp{other};
  this->swap(tmp);

  return *this;
}

template <typename value_type>
queue<value_type>& queue<value_type>::operator=(queue<value_type>&& other) {
  if (this == &other) {
    return *this;
  }

  queue<value_type> tmp{std::move(other)};
  this->swap(tmp);

  return *this;
}

template <typename value_type>
typename queue<value_type>::const_reference queue<value_type>::front() const {
  return data_.front();
}

template <typename value_type>
typename queue<value_type>::const_reference queue<value_type>::back() const {
  return data_.back();
}

template <typename value_type>
void queue<value_type>::push(const_reference value) {
  data_.push_back(value);
}

template <typename value_type>
void queue<value_type>::pop() {
  data_.pop_front();
}

template <typename value_type>
template <typename... Args>
void queue<value_type>::insert_many_back(Args&&... args) {
  for (auto arg : {args...}) {
    push(arg);
  }
}

}  // namespace s21

#endif  // SRC_CORE_S21_QUEUE_H_